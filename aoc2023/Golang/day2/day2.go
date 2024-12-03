package aoc2023day2

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func processFile(filename string, processLine func(line string, index int) int) int {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return 0
	}
	defer file.Close()

	input := bufio.NewScanner(file)
	result := 0
	index := 1
	for input.Scan() {
		result += processLine(input.Text(), index)
		index++
	}
	return result
}

func processPart2Line(line string, index int) int {
	power := [3]int{}
	draws := strings.Split(line[strings.Index(line, ": ")+2:], "; ")
	for _, draw := range draws {
		rgb := strings.Split(draw, ", ")
		for _, colorComponent := range rgb {
			fields := strings.Fields(colorComponent)
			count := atoi(fields[0])
			color := fields[1]

			var colorIndex int
			switch color {
			case "red":
				colorIndex = R
			case "green":
				colorIndex = G
			case "blue":
				colorIndex = B
			}

			power[colorIndex] = max(power[colorIndex], count)
		}
	}
	return power[B] * power[G] * power[R]
}

func processPart1Line(line string, index int) int {
	valid := true
	draws := strings.Split(line[strings.Index(line, ": ")+2:], "; ")
	maxRed, maxGreen, maxBlue := 12, 13, 14

	for _, draw := range draws {
		rgb := strings.Split(draw, ", ")
		for _, colorComponent := range rgb {
			fields := strings.Fields(colorComponent)
			count := atoi(fields[0])
			color := fields[1]

			switch color {
			case "red":
				if count > maxRed {
					valid = false
				}
			case "green":
				if count > maxGreen {
					valid = false
				}
			case "blue":
				if count > maxBlue {
					valid = false
				}
			}
		}
	}

	if valid {
		return index
	}
	return 0
}

func part1(filename string) {
	fmt.Print("Part 1: ")
	idsum := processFile(filename, processPart1Line)
	fmt.Println("ID sum =", idsum)
}

func part2(filename string) {
	fmt.Print("Part 2: ")
	pwsum := processFile(filename, processPart2Line)
	fmt.Println("PW sum =", pwsum)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 2 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}

const (
	B = iota
	G
	R
)

func atoi(s string) (n int) {
	for i := range s {
		n = 10*n + int(s[i]-'0')
	}
	return
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
