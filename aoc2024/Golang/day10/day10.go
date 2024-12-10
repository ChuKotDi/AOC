package aoc2024day10

import (
	"bufio"
	"fmt"
	"os"
)

func readMap(filename string) [][]int {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer func(file *os.File) {
		err := file.Close()
		if err != nil {
			fmt.Println("Error reading input:", err)
			return
		}
	}(file)

	var topoMap [][]int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		row := make([]int, len(line))
		for i, char := range line {
			row[i] = int(char - '0')
		}
		topoMap = append(topoMap, row)
	}
	if err := scanner.Err(); err != nil {
		panic(err)
	}
	return topoMap
}

func calculateTrailScore(topoMap [][]int, startX, startY int) int {
	rows, cols := len(topoMap), len(topoMap[0])
	visited := make(map[[2]int]bool)
	queue := [][2]int{{startX, startY}}
	visited[[2]int{startX, startY}] = true
	score := 0

	directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]
		x, y := current[0], current[1]

		if topoMap[x][y] == 9 {
			score++
			continue
		}

		for _, dir := range directions {
			nx, ny := x+dir[0], y+dir[1]
			if nx >= 0 && ny >= 0 && nx < rows && ny < cols && !visited[[2]int{nx, ny}] {
				if topoMap[nx][ny] == topoMap[x][y]+1 { // Проверяем увеличение высоты ровно на 1
					queue = append(queue, [2]int{nx, ny})
					visited[[2]int{nx, ny}] = true
				}
			}
		}
	}

	return score
}

func part1(filename string) {
	topoMap := readMap(filename)
	rows, cols := len(topoMap), len(topoMap[0])
	totalScore := 0

	for x := 0; x < rows; x++ {
		for y := 0; y < cols; y++ {
			if topoMap[x][y] == 0 {
				totalScore += calculateTrailScore(topoMap, x, y)
			}
		}
	}

	fmt.Println("Part 1:", totalScore)
}

func countTrails(topoMap [][]int, x, y int, memo map[[2]int]int) int {
	rows, cols := len(topoMap), len(topoMap[0])

	if value, exists := memo[[2]int{x, y}]; exists {
		return value
	}

	if topoMap[x][y] == 9 {
		return 1
	}

	directions := [][2]int{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
	totalTrails := 0

	for _, dir := range directions {
		nx, ny := x+dir[0], y+dir[1]
		if nx >= 0 && ny >= 0 && nx < rows && ny < cols && topoMap[nx][ny] == topoMap[x][y]+1 {
			totalTrails += countTrails(topoMap, nx, ny, memo)
		}
	}

	memo[[2]int{x, y}] = totalTrails
	return totalTrails
}

func part2(filename string) {
	topoMap := readMap(filename)
	rows, cols := len(topoMap), len(topoMap[0])
	totalRating := 0
	memo := make(map[[2]int]int)

	for x := 0; x < rows; x++ {
		for y := 0; y < cols; y++ {
			if topoMap[x][y] == 0 {
				totalRating += countTrails(topoMap, x, y, memo)
			}
		}
	}

	fmt.Println("Part 2:", totalRating)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 10 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
