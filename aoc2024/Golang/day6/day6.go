package aoc2024day6

import (
	"bufio"
	"fmt"
	"os"
)

type Position struct {
	x, y int
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 6 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}

func part1(filename string) {
	fmt.Print("Part 1: ")

	grid, err := readGridFromFile(filename)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}

	startPos, direction := findGuardStart(grid)
	if startPos == (Position{-1, -1}) {
		fmt.Println("Guard not found on the map.")
		return
	}

	visited := make(map[Position]bool)
	visited[startPos] = true

	currentPos := startPos
	for {
		nextPos := move(currentPos, direction)

		if nextPos.x < 0 || nextPos.y < 0 || nextPos.x >= len(grid[0]) || nextPos.y >= len(grid) {
			break
		}

		if grid[nextPos.y][nextPos.x] == '#' {
			direction = turnRight(direction)
		} else {
			currentPos = nextPos
			visited[currentPos] = true
		}
	}

	fmt.Printf("Guard visited %d unique positions.\n", len(visited))
}

func part2(filename string) {
	fmt.Print("Part 2: ")

	grid, err := readGridFromFile(filename)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}

	startPos, direction := findGuardStart(grid)
	if startPos == (Position{-1, -1}) {
		fmt.Println("Guard not found on the map.")
		return
	}

	loopPositions := findLoopPositions(grid, startPos, direction)

	fmt.Printf("Number of possible positions for a new obstacle = %d\n", len(loopPositions))
}

func readGridFromFile(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var grid []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		grid = append(grid, scanner.Text())
	}
	return grid, scanner.Err()
}

func findGuardStart(grid []string) (Position, string) {
	directions := "^>v<"
	for y, row := range grid {
		for x, cell := range row {
			if idx := directionsIndex(directions, cell); idx != -1 {
				return Position{x, y}, string(directions[idx])
			}
		}
	}
	return Position{-1, -1}, ""
}

func directionsIndex(directions string, char rune) int {
	for i, d := range directions {
		if d == char {
			return i
		}
	}
	return -1
}

func move(pos Position, direction string) Position {
	switch direction {
	case "^":
		return Position{pos.x, pos.y - 1}
	case ">":
		return Position{pos.x + 1, pos.y}
	case "v":
		return Position{pos.x, pos.y + 1}
	case "<":
		return Position{pos.x - 1, pos.y}
	}
	return pos
}

func turnRight(direction string) string {
	directions := "^>v<"
	idx := directionsIndex(directions, rune(direction[0]))
	return string(directions[(idx+1)%4])
}

func findLoopPositions(grid []string, startPos Position, startDir string) []Position {
	var loopPositions []Position

	for y, row := range grid {
		for x, cell := range row {
			pos := Position{x, y}

			if pos == startPos || cell == '#' {
				continue
			}

			modifiedGrid := addObstacle(grid, pos)

			if isGuardStuck(modifiedGrid, startPos, startDir) {
				loopPositions = append(loopPositions, pos)
			}
		}
	}

	return loopPositions
}

func isGuardStuck(grid []string, startPos Position, startDir string) bool {
	visited := make(map[Position]map[string]bool)
	currentPos := startPos
	direction := startDir

	for steps := 0; steps < 10000; steps++ {
		if visited[currentPos] != nil && visited[currentPos][direction] {
			return true
		}

		if visited[currentPos] == nil {
			visited[currentPos] = make(map[string]bool)
		}
		visited[currentPos][direction] = true

		nextPos := move(currentPos, direction)

		if nextPos.x < 0 || nextPos.y < 0 || nextPos.x >= len(grid[0]) || nextPos.y >= len(grid) {
			return false
		}

		if grid[nextPos.y][nextPos.x] == '#' {
			direction = turnRight(direction)
		} else {
			currentPos = nextPos
		}
	}

	return false
}

func addObstacle(grid []string, pos Position) []string {
	modifiedGrid := make([]string, len(grid))
	copy(modifiedGrid, grid)
	row := []rune(modifiedGrid[pos.y])
	row[pos.x] = '#'
	modifiedGrid[pos.y] = string(row)
	return modifiedGrid
}
