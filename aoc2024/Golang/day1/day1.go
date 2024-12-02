package aoc2024day1

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func readListsFromFile(filename string) ([]int, []int, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, nil, fmt.Errorf("file read error: %w", err)
	}
	defer func(file *os.File) {
		err := file.Close()
		if err != nil {

		}
	}(file)

	var leftList, rightList []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		nums := strings.Fields(line)
		if len(nums) != 2 {
			return nil, nil, fmt.Errorf("invalid string format: %s", line)
		}

		leftNum, err := strconv.Atoi(nums[0])
		if err != nil {
			return nil, nil, fmt.Errorf("the number could not be converted: %w", err)
		}
		rightNum, err := strconv.Atoi(nums[1])
		if err != nil {
			return nil, nil, fmt.Errorf("the number could not be converted: %w", err)
		}

		leftList = append(leftList, leftNum)
		rightList = append(rightList, rightNum)
	}

	if err := scanner.Err(); err != nil {
		return nil, nil, fmt.Errorf("file read error: %w", err)
	}

	return leftList, rightList, nil
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func calculateTotalDistance(leftList, rightList []int) int {
	sort.Ints(leftList)
	sort.Ints(rightList)

	totalDistance := 0
	for i := 0; i < len(leftList); i++ {
		totalDistance += abs(leftList[i] - rightList[i])
	}
	return totalDistance
}

func calculateSimilarity(leftList, rightList []int) int {
	rightCount := make(map[int]int)
	for _, num := range rightList {
		rightCount[num]++
	}

	totalSimilarity := 0
	for _, num := range leftList {
		totalSimilarity += num * rightCount[num]
	}
	return totalSimilarity
}

func day1Part1(filename string) {
	leftList, rightList, err := readListsFromFile(filename)
	if err != nil {
		fmt.Println("File read error Part 1:", err)
		return
	}

	totalDistance := calculateTotalDistance(leftList, rightList)
	fmt.Printf("Part 1: Total distance = %d\n", totalDistance)
}

func day1Part2(filename string) {
	leftList, rightList, err := readListsFromFile(filename)
	if err != nil {
		fmt.Println("File read error Part 2:", err)
		return
	}

	totalSimilarity := calculateSimilarity(leftList, rightList)
	fmt.Printf("Part 2: Total similarity = %d\n", totalSimilarity)
}

func Day1(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 1 Results:")
	day1Part1(filenamePart1)
	day1Part2(filenamePart2)
}
