package aoc2024day3

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func readInputFromFile(filename string) (string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return "", err
	}
	defer file.Close()

	var data string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		data += scanner.Text()
	}

	if err := scanner.Err(); err != nil {
		return "", err
	}

	return data, nil
}

func sumValidMulExpressions(input string) int {
	re := regexp.MustCompile(`mul\((\d+),(\d+)\)`)
	matches := re.FindAllStringSubmatch(input, -1)

	sum := 0
	for _, match := range matches {
		x, _ := strconv.Atoi(match[1])
		y, _ := strconv.Atoi(match[2])
		sum += x * y
	}

	return sum
}

func part1(filename string) {
	input, err := readInputFromFile(filename)
	if err != nil {
		fmt.Println("Fail read file:", err)
		return
	}

	result := sumValidMulExpressions(input)

	fmt.Println("Part1: results sum = ", result)
}

func sumValidMulExpressionsWithConditions(input string) int {
	mulRegex := regexp.MustCompile(`mul\((\d+),(\d+)\)`)
	doRegex := regexp.MustCompile(`do\(\)`)
	dontRegex := regexp.MustCompile(`don't\(\)`)

	mulEnabled := true
	sum := 0

	pos := 0
	for pos < len(input) {
		if doMatch := doRegex.FindStringIndex(input[pos:]); doMatch != nil && doMatch[0] == 0 {
			mulEnabled = true
			pos += doMatch[1]
			continue
		}

		if dontMatch := dontRegex.FindStringIndex(input[pos:]); dontMatch != nil && dontMatch[0] == 0 {
			mulEnabled = false
			pos += dontMatch[1]
			continue
		}

		if mulMatch := mulRegex.FindStringSubmatchIndex(input[pos:]); mulMatch != nil && mulMatch[0] == 0 {
			if mulEnabled {
				x, _ := strconv.Atoi(input[pos+mulMatch[2] : pos+mulMatch[3]])
				y, _ := strconv.Atoi(input[pos+mulMatch[4] : pos+mulMatch[5]])
				sum += x * y
			}
			pos += mulMatch[1]
			continue
		}

		pos++
	}

	return sum
}

func part2(filename string) {
	input, err := readInputFromFile(filename)
	if err != nil {
		fmt.Println("Fail read file:", err)
		return
	}

	result := sumValidMulExpressionsWithConditions(input)

	fmt.Println("Part2: results sum = ", result)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 3 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
