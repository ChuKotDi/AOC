package aoc2024day19

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func readInput(filename string) ([]string, []string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, nil, err
	}
	defer file.Close()

	var towelPatterns []string
	var desiredDesigns []string

	scanner := bufio.NewScanner(file)
	isDesignSection := false

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			isDesignSection = true
			continue
		}
		if !isDesignSection {
			patterns := strings.Split(line, ", ")
			towelPatterns = append(towelPatterns, patterns...)
		} else {
			desiredDesigns = append(desiredDesigns, line)
		}
	}

	if err := scanner.Err(); err != nil {
		return nil, nil, err
	}

	return towelPatterns, desiredDesigns, nil
}

func countWaysToMakeDesign(patterns []string, design string) int {
	patternMap := make(map[string]bool)
	for _, pattern := range patterns {
		patternMap[pattern] = true
	}

	memo := make(map[string]int)
	var dfs func(remaining string) int

	dfs = func(remaining string) int {
		if remaining == "" {
			return 1
		}
		if result, exists := memo[remaining]; exists {
			return result
		}
		ways := 0
		for i := 1; i <= len(remaining); i++ {
			prefix := remaining[:i]
			if patternMap[prefix] {
				ways += dfs(remaining[i:])
			}
		}
		memo[remaining] = ways
		return ways
	}

	return dfs(design)
}

func part1(filename string) {
	towelPatterns, desiredDesigns, err := readInput(filename)
	if err != nil {
		fmt.Println("Error reading input:", err)
		return
	}

	successCount := 0
	for _, design := range desiredDesigns {
		if countWaysToMakeDesign(towelPatterns, design) > 0 {
			successCount++
		}
	}

	fmt.Printf("Part 1: %d designs are possible\n", successCount)
}

func part2(filename string) {
	towelPatterns, desiredDesigns, err := readInput(filename)
	if err != nil {
		fmt.Println("Error reading input:", err)
		return
	}

	totalWays := 0
	for _, design := range desiredDesigns {
		totalWays += countWaysToMakeDesign(towelPatterns, design)
	}

	fmt.Printf("Part 2: Total ways to make designs = %d\n", totalWays)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 19 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
