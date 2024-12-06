package aoc2023day6

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func Day(filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open file: %v\n", err)
		os.Exit(1)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	times, combinedTime := parseInput(scanner)
	distances, combinedDistance := parseInput(scanner)

	calculateSolutions := func(time, distance int) int {
		delta := calculateIntegerSquareRoot(time*time - 4*distance)

		lowerRoot := (time - delta) / 2
		upperRoot := time - lowerRoot

		if lowerRoot*(time-lowerRoot) <= distance {
			lowerRoot++
		}

		if upperRoot*(time-upperRoot) <= distance {
			upperRoot--
		}

		return upperRoot - lowerRoot + 1
	}

	totalSolutions := 1
	for i := range times {
		totalSolutions *= calculateSolutions(times[i], distances[i])
	}

	fmt.Println("Day 6 Results:")
	fmt.Println("Part 1:", totalSolutions)
	fmt.Println("Part 2:", calculateSolutions(combinedTime, combinedDistance))
}

func parseInput(scanner *bufio.Scanner) ([]int, int) {
	scanner.Scan()
	line := scanner.Text()
	values := strings.Fields(line[strings.Index(line, ":")+1:])

	numbers := make([]int, 0, len(values))
	var concatenatedValues strings.Builder
	for _, value := range values {
		number := convertStringToInt(value)
		numbers = append(numbers, number)
		concatenatedValues.WriteString(value)
	}

	return numbers, convertStringToInt(concatenatedValues.String())
}

func convertStringToInt(input string) int {
	result := 0
	for _, char := range input {
		result = 10*result + int(char-'0')
	}
	return result
}

func calculateIntegerSquareRoot(value int) int {
	value64 := uint64(value)
	var root, bit, temp uint64
	for bit = uint64(1 << ((logBase2(value64) >> 1) << 1)); bit != 0; bit >>= 2 {
		temp = root | bit
		root >>= 1
		if value64 >= temp {
			value64 -= temp
			root |= bit
		}
	}
	return int(root)
}

func logBase2(value uint64) uint64 {
	value |= value >> 1
	value |= value >> 2
	value |= value >> 4
	value |= value >> 8
	value |= value >> 16
	value |= value >> 32
	return lookupTable[((value-(value>>1))*0x07EDD5E59A4E28C2)>>58]
}

var lookupTable = [64]uint64{
	63, 0, 58, 1, 59, 47, 53, 2,
	60, 39, 48, 27, 54, 33, 42, 3,
	61, 51, 37, 40, 49, 18, 28, 20,
	55, 30, 34, 11, 43, 14, 22, 4,
	62, 57, 46, 52, 38, 26, 32, 41,
	50, 36, 17, 19, 29, 10, 13, 21,
	56, 45, 25, 31, 35, 16, 9, 12,
	44, 24, 15, 8, 23, 7, 6, 5,
}
