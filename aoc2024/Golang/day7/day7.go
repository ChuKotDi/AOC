package aoc2024day7

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func parseInput(filename string) ([]int, [][]int, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, nil, err
	}
	defer file.Close()

	var targets []int
	var numbers [][]int

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ":")
		if len(parts) != 2 {
			return nil, nil, fmt.Errorf("invalid line format: %s", line)
		}

		target, err := strconv.Atoi(strings.TrimSpace(parts[0]))
		if err != nil {
			return nil, nil, fmt.Errorf("invalid target value: %s", parts[0])
		}
		targets = append(targets, target)

		nums := strings.Fields(parts[1])
		var sequence []int
		for _, num := range nums {
			value, err := strconv.Atoi(num)
			if err != nil {
				return nil, nil, fmt.Errorf("invalid number in sequence: %s", num)
			}
			sequence = append(sequence, value)
		}
		numbers = append(numbers, sequence)
	}

	if err := scanner.Err(); err != nil {
		return nil, nil, err
	}

	return targets, numbers, nil
}

func canReachTarget(target int, numbers []int) bool {
	if len(numbers) == 0 {
		return false
	}

	var evaluate func(int, int) bool
	evaluate = func(index int, currentValue int) bool {
		if index == len(numbers) {
			return currentValue == target
		}

		if evaluate(index+1, currentValue+numbers[index]) {
			return true
		}

		if evaluate(index+1, currentValue*numbers[index]) {
			return true
		}

		return false
	}

	return evaluate(1, numbers[0])
}

func part1(filename string) {
	targets, numbers, err := parseInput(filename)
	if err != nil {
		fmt.Println("Error reading input:", err)
		return
	}

	totalResult := 0
	for i, target := range targets {
		if canReachTarget(target, numbers[i]) {
			totalResult += target
		}
	}

	fmt.Println("Part 1:", totalResult)
}

func canReachTargetWithConcat(target int, numbers []int) bool {
	if len(numbers) == 0 {
		return false
	}

	var evaluate func(int, int) bool
	evaluate = func(index int, currentValue int) bool {
		if index == len(numbers) {
			return currentValue == target
		}

		if evaluate(index+1, currentValue+numbers[index]) {
			return true
		}

		if evaluate(index+1, currentValue*numbers[index]) {
			return true
		}

		concatValue, _ := strconv.Atoi(fmt.Sprintf("%d%d", currentValue, numbers[index]))
		if evaluate(index+1, concatValue) {
			return true
		}

		return false
	}

	return evaluate(1, numbers[0])
}

func part2(filename string) {
	targets, numbers, err := parseInput(filename)
	if err != nil {
		fmt.Println("Error reading input:", err)
		return
	}

	totalResult := 0
	for i, target := range targets {
		if canReachTargetWithConcat(target, numbers[i]) {
			totalResult += target
		}
	}

	fmt.Println("Part 2:", totalResult)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 7 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
