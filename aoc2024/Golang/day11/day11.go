package aoc2024day11

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func part1(filename string) {
	initialStones := readInput(filename)

	blinks := 25
	count := countStonesEfficiently(initialStones, blinks)
	fmt.Println("Part 1:", count)
}

func part2(filename string) {
	initialStones := readInput(filename)

	blinks := 75
	count := countStonesEfficiently(initialStones, blinks)

	fmt.Println("Part 2:", count)
}

func countStonesEfficiently(stones []int, blinks int) int {
	stoneCounts := make(map[int]int)

	for _, stone := range stones {
		stoneCounts[stone]++
	}

	for i := 0; i < blinks; i++ {
		newCounts := make(map[int]int)

		for stone, count := range stoneCounts {
			switch {
			case stone == 0:
				newCounts[1] += count

			case evenDigits(stone):
				left, right := splitNumber(stone)
				newCounts[left] += count
				newCounts[right] += count

			default:
				newCounts[stone*2024] += count
			}
		}

		stoneCounts = newCounts
	}

	totalCount := 0
	for _, count := range stoneCounts {
		totalCount += count
	}
	return totalCount
}

func evenDigits(num int) bool {
	return len(strconv.Itoa(num))%2 == 0
}

func splitNumber(num int) (int, int) {
	numStr := strconv.Itoa(num)
	mid := len(numStr) / 2
	left, _ := strconv.Atoi(numStr[:mid])
	right, _ := strconv.Atoi(numStr[mid:])
	return left, right
}

func readInput(filename string) []int {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var stones []int

	for scanner.Scan() {
		line := scanner.Text()
		for _, numStr := range strings.Fields(line) {
			num, _ := strconv.Atoi(numStr)
			stones = append(stones, num)
		}
	}
	return stones
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 11 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
