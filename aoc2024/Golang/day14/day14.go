package aoc2024day14

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"
)

const (
	Height       = 7
	Width        = 11
	InitialSteps = 100
	MaxRobots    = 500
	Threshold    = 25
)

type Coordinates struct {
	X, Y int
}

type Robot struct {
	Position Coordinates
	Velocity Coordinates
}

func Day(filename string) {
	fmt.Println("Day 14 Results:")
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var robots []Robot

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		fields := strings.Fields(scanner.Text())
		positionData := strings.Split(fields[0], ",")
		velocityData := strings.Split(fields[1], ",")

		robots = append(robots, Robot{
			Position: Coordinates{X: parseInt(positionData[0][2:]), Y: parseInt(positionData[1])},
			Velocity: Coordinates{X: parseInt(velocityData[0][2:]), Y: parseInt(velocityData[1])},
		})
	}

	var steps, stableX, stableY int
	for steps < InitialSteps && (stableX == 0 || stableY == 0) {
		stdDevX, stdDevY := calculateStandardDeviation(robots)
		if stdDevY < Threshold {
			stableY = steps
		}
		if stdDevX < Threshold {
			stableX = steps
		}
		robots = moveRobots(robots, 1)
		steps++
	}

	robots = moveRobots(robots, InitialSteps-steps)
	part1Result := calculateProductOfQuadrants(robots)

	part2Result := findSynchronizedTime(stableX, stableY)
	robots = moveRobots(robots, part2Result-InitialSteps)

	fmt.Printf("Part 1: %d\n", part1Result)
	fmt.Printf("Part 2: %d\n", part2Result)
}

func moveRobots(robots []Robot, steps int) []Robot {
	for i := range robots {
		robots[i].Position.X = modular(robots[i].Position.X+steps*robots[i].Velocity.X, Width)
		robots[i].Position.Y = modular(robots[i].Position.Y+steps*robots[i].Velocity.Y, Height)
	}
	return robots
}

func calculateProductOfQuadrants(robots []Robot) int {
	quadrants := countRobotsInQuadrants(robots)
	product := 1
	for _, count := range quadrants {
		product *= count
	}
	return product
}

func countRobotsInQuadrants(robots []Robot) [4]int {
	centerX, centerY := Width/2, Height/2
	quadrantCounts := [4]int{}

	for _, robot := range robots {
		position := robot.Position
		switch {
		case position.X < centerX && position.Y > centerY:
			quadrantCounts[0]++
		case position.X < centerX && position.Y < centerY:
			quadrantCounts[1]++
		case position.X > centerX && position.Y < centerY:
			quadrantCounts[2]++
		case position.X > centerX && position.Y > centerY:
			quadrantCounts[3]++
		}
	}
	return quadrantCounts
}

func modular(a, b int) int {
	return ((a % b) + b) % b
}

func parseInt(input string) int {
	sign := 1
	if input[0] == '-' {
		sign, input = -1, input[1:]
	}
	number := 0
	for _, char := range input {
		number = number*10 + int(char-'0')
	}
	return number * sign
}

func createSampleMatrix(robots []Robot) [][]int {
	matrix := make([][]int, Height)
	for i := range matrix {
		matrix[i] = make([]int, Width)
	}
	for _, robot := range robots[:len(robots)/2] {
		matrix[robot.Position.Y][robot.Position.X] = 1
	}
	return matrix
}

func calculateStandardDeviation(robots []Robot) (float64, float64) {
	sample := createSampleMatrix(robots)
	var xCoords, yCoords []int

	for y, row := range sample {
		for x, value := range row {
			if value == 1 {
				xCoords = append(xCoords, x)
				yCoords = append(yCoords, y)
			}
		}
	}

	meanX, meanY := calculateMean(xCoords), calculateMean(yCoords)
	return calculateStdDev(xCoords, meanX), calculateStdDev(yCoords, meanY)
}

func calculateMean(values []int) float64 {
	sum := 0
	for _, value := range values {
		sum += value
	}
	return float64(sum) / float64(len(values))
}

func calculateStdDev(values []int, mean float64) float64 {
	var sum float64
	for _, value := range values {
		sum += math.Pow(float64(value)-mean, 2)
	}
	return math.Sqrt(sum / float64(len(values)))
}

func findSynchronizedTime(stableX, stableY int) int {
	periodX, periodY := Height, Width
	modDiff := modular(stableY-stableX, periodY)
	inverse := modularInverse(periodX%periodY, periodY)
	k := (modDiff * inverse) % periodY

	return k*periodX + stableX
}

func modularInverse(a, mod int) int {
	modulus, x0, x1 := mod, 0, 1
	for a > 1 {
		quotient := a / mod
		a, mod = mod, a%mod
		x0, x1 = x1-quotient*x0, x0
	}
	if x1 < 0 {
		x1 += modulus
	}
	return x1
}
