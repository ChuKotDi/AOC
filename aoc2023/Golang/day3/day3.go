package aoc2023day3

import (
	"bufio"
	"fmt"
	"os"
	"unicode"
)

type Coordinate struct {
	x, y int
}

func isValidCoordinate(x, y, rows, cols int) bool {
	return x >= 0 && x < rows && y >= 0 && y < cols
}

func isValidNumber(engineLayout []string, x, y, rows, cols int, stars map[Coordinate]struct{}) bool {
	dx := []int{-1, -1, -1, 0, 0, 1, 1, 1}
	dy := []int{-1, 0, 1, -1, 1, -1, 0, 1}

	for i := 0; i < 8; i++ {
		newX, newY := x+dx[i], y+dy[i]

		if isValidCoordinate(newX, newY, rows, cols) && engineLayout[newX][newY] != '.' && !unicode.IsDigit(rune(engineLayout[newX][newY])) {
			if engineLayout[newX][newY] == '*' {
				stars[Coordinate{newX, newY}] = struct{}{}
			}
			return true
		}
	}

	return false
}

func sumAdjacentNumbers(engineLayout []string, x, y int, starDigits map[Coordinate][]int) int {
	rows, cols := len(engineLayout), len(engineLayout[0])
	num := 0
	isValid := false
	stars := make(map[Coordinate]struct{})

	currentNumber := ""

	for isValidCoordinate(x, y, rows, cols) {
		if unicode.IsDigit(rune(engineLayout[x][y])) {
			digit := engineLayout[x][y] - '0'
			num = num*10 + int(digit)

			currentNumber += fmt.Sprintf("%d", digit)
		} else {
			break
		}

		if isValidNumber(engineLayout, x, y, rows, cols, stars) {
			isValid = true
		}

		y++
	}

	if isValid {
		for star := range stars {
			starDigits[star] = append(starDigits[star], num)
		}
		return num
	}

	return 0
}

func processEngineLayout(filename string, process func(engineLayout []string) int) int {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Unable to open the file:", err)
		return 0
	}
	defer file.Close()

	var engineLayout []string
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		engineLayout = append(engineLayout, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error reading the file:", err)
		return 0
	}

	return process(engineLayout)
}

func part1(filename string) {
	totalSum := processEngineLayout(filename, func(engineLayout []string) int {
		starDigits := make(map[Coordinate][]int)
		totalSum := 0

		for i := 0; i < len(engineLayout); i++ {
			for j := 0; j < len(engineLayout[i]); j++ {
				if unicode.IsDigit(rune(engineLayout[i][j])) {
					totalSum += sumAdjacentNumbers(engineLayout, i, j, starDigits)
					for j < len(engineLayout[i]) && unicode.IsDigit(rune(engineLayout[i][j])) {
						j++
					}
				}
			}
		}
		return totalSum
	})

	fmt.Println("Part1: The sum of adjacent numbers in the engine layout is =", totalSum)
}

func part2(filename string) {
	totalSum := processEngineLayout(filename, func(engineLayout []string) int {
		starDigits := make(map[Coordinate][]int)
		totalSum := 0

		for i := 0; i < len(engineLayout); i++ {
			for j := 0; j < len(engineLayout[i]); j++ {
				if unicode.IsDigit(rune(engineLayout[i][j])) {
					sumAdjacentNumbers(engineLayout, i, j, starDigits)
					for j < len(engineLayout[i]) && unicode.IsDigit(rune(engineLayout[i][j])) {
						j++
					}
				}
			}
		}

		for _, numbers := range starDigits {
			if len(numbers) == 2 {
				totalSum += numbers[0] * numbers[1]
			}
		}

		return totalSum
	})

	fmt.Println("Part2: The sum of all gear ratios is =", totalSum)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 3 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
