package aoc2024day2

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readReportsFromFile(filename string) ([][]int, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, fmt.Errorf("the file could not be opened: %w", err)
	}
	defer func(file *os.File) {
		err := file.Close()
		if err != nil {

		}
	}(file)

	var reports [][]int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		nums := strings.Fields(line)
		var levels []int
		for _, num := range nums {
			level, err := strconv.Atoi(num)
			if err != nil {
				return nil, fmt.Errorf("number conversion error: %w", err)
			}
			levels = append(levels, level)
		}
		reports = append(reports, levels)
	}

	if err := scanner.Err(); err != nil {
		return nil, fmt.Errorf("file reading error: %w", err)
	}

	return reports, nil
}

func isSafeReport(levels []int) bool {
	return checkMonotonicity(levels, -1)
}

func canBeMadeSafe(levels []int) bool {
	for i := 0; i < len(levels); i++ {
		if checkMonotonicity(levels, i) {
			return true
		}
	}
	return false
}

func checkMonotonicity(levels []int, skipIndex int) bool {
	increasing, decreasing := true, true
	prev := -1

	for i := 0; i < len(levels); i++ {
		if i == skipIndex {
			continue
		}
		if prev != -1 {
			diff := abs(levels[i] - levels[prev])
			if diff < 1 || diff > 3 {
				return false
			}
			if levels[i] < levels[prev] {
				increasing = false
			}
			if levels[i] > levels[prev] {
				decreasing = false
			}
		}
		prev = i
	}

	return increasing || decreasing
}

func day2Part1(filename string) {
	reports, err := readReportsFromFile(filename)
	if err != nil {
		fmt.Println("File read error Part 1:", err)
		return
	}

	safeReportsCount := 0
	for _, report := range reports {
		if isSafeReport(report) {
			safeReportsCount++
		}
	}

	fmt.Println("Part 1: safe report count =", safeReportsCount)
}

func day2Part2(filename string) {
	reports, err := readReportsFromFile(filename)
	if err != nil {
		fmt.Println("File read error Part 2:", err)
		return
	}

	safeCount := 0
	for _, report := range reports {
		if isSafeReport(report) || canBeMadeSafe(report) {
			safeCount++
		}
	}

	fmt.Println("Part 2: safe report count =", safeCount)
}

func Day2(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 2 Results:")
	day2Part1(filenamePart1)
	day2Part2(filenamePart2)
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
