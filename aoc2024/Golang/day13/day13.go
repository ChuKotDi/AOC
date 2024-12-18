package aoc2024day13

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func Day(filename string) {
	fmt.Println("Day 13 Results:")
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close()

	var part1Sum, part2Sum int
	currentSystem := make([]int, 0, 4)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		switch {
		case line == "":
			currentSystem = currentSystem[:0]
		case line[0] == 'B':
			buttonCoordinates := parseCoordinates(line[10:])
			currentSystem = append(currentSystem, buttonCoordinates...)
		case line[0] == 'P':
			targetCoordinates := parseCoordinates(line[7:])
			currentSystem = append(currentSystem, targetCoordinates...)

			a, b := solveSystem(currentSystem, 0)
			part1Sum += a*3 + b

			a, b = solveSystem(currentSystem, 10_000_000_000_000)
			part2Sum += a*3 + b
		}
	}

	fmt.Printf("Part 1: %d\n", part1Sum)
	fmt.Printf("Part 2: %d\n", part2Sum)
}

func parseCoordinates(input string) []int {
	parts := strings.Split(input, ", ")
	return []int{convertToInt(parts[0][2:]), convertToInt(parts[1][2:])}
}

func convertToInt(s string) (result int) {
	for i := range s {
		result = 10*result + int(s[i]-'0')
	}
	return
}

func solveSystem(system []int, offset int) (int, int) {
	ax, ay, bx, by, targetX, targetY := system[0], system[1], system[2], system[3], system[4], system[5]
	targetX += offset
	targetY += offset

	determinant := ax*by - ay*bx
	if determinant == 0 {
		return 0, 0
	}

	a := (targetX*by - targetY*bx) / determinant
	b := (ax*targetY - targetX*ay) / determinant

	if a < 0 || b < 0 || a*ax != targetX-b*bx || a*ay != targetY-b*by {
		return 0, 0
	}

	return a, b
}
