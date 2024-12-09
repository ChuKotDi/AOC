package aoc2024day9

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func compactAndCalculateChecksum(diskMap string) int {
	blocks := []int{}
	currentID := -1
	for i := 0; i < len(diskMap); i++ {
		length, err := strconv.Atoi(string(diskMap[i]))
		if err != nil {
			fmt.Printf("Invalid character in input: %s\n", string(diskMap[i]))
			return 0
		}

		if i%2 == 0 {
			currentID++
			for j := 0; j < length; j++ {
				blocks = append(blocks, currentID)
			}
		} else {
			for j := 0; j < length; j++ {
				blocks = append(blocks, -1)
			}
		}
	}

	for {
		moved := false

		for i := len(blocks) - 1; i >= 0; i-- {
			if blocks[i] != -1 {
				freeIndex := -1
				for j := 0; j < i; j++ {
					if blocks[j] == -1 {
						freeIndex = j
						break
					}
				}

				if freeIndex != -1 {
					blocks[freeIndex], blocks[i] = blocks[i], -1
					moved = true
					break
				}
			}
		}

		if !moved {
			break
		}
	}

	checksum := 0
	for pos, fileID := range blocks {
		if fileID != -1 {
			checksum += pos * fileID
		}
	}

	return checksum
}

func readInput(filename string) (string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return "", err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	if scanner.Scan() {
		return strings.TrimSpace(scanner.Text()), nil
	}

	return "", fmt.Errorf("file is empty or not readable")
}

func part1(filename string) {
	diskMap, err := readInput(filename)
	if err != nil {
		fmt.Printf("Error reading file: %v\n", err)
		return
	}

	checksum := compactAndCalculateChecksum(diskMap)
	fmt.Printf("Part1: Checksum = %d\n", checksum)
}

func compactFilesAndCalculateChecksum(diskMap string) int {
	blocks := []int{}
	currentID := -1
	fileLengths := map[int]int{}
	for i := 0; i < len(diskMap); i++ {
		length, err := strconv.Atoi(string(diskMap[i]))
		if err != nil {
			fmt.Printf("Invalid character in input: %s\n", string(diskMap[i]))
			return 0
		}

		if i%2 == 0 {
			currentID++
			fileLengths[currentID] = length
			for j := 0; j < length; j++ {
				blocks = append(blocks, currentID)
			}
		} else {
			for j := 0; j < length; j++ {
				blocks = append(blocks, -1)
			}
		}
	}

	for fileID := currentID; fileID >= 0; fileID-- {
		fileLength := fileLengths[fileID]

		fileStart, fileEnd := -1, -1
		for i, block := range blocks {
			if block == fileID {
				if fileStart == -1 {
					fileStart = i
				}
				fileEnd = i
			}
		}

		targetStart := -1
		freeCount := 0
		for i := 0; i < fileStart; i++ {
			if blocks[i] == -1 {
				if targetStart == -1 {
					targetStart = i
				}
				freeCount++
				if freeCount == fileLength {
					break
				}
			} else {
				targetStart = -1
				freeCount = 0
			}
		}

		if freeCount == fileLength {
			for i := fileStart; i <= fileEnd; i++ {
				blocks[i] = -1
			}
			for i := 0; i < fileLength; i++ {
				blocks[targetStart+i] = fileID
			}
		}
	}

	checksum := 0
	for pos, fileID := range blocks {
		if fileID != -1 {
			checksum += pos * fileID
		}
	}

	return checksum
}

func part2(filename string) {
	diskMap, err := readInput(filename)
	if err != nil {
		fmt.Printf("Error reading file: %v\n", err)
		return
	}

	checksum := compactFilesAndCalculateChecksum(diskMap)
	fmt.Printf("Part2: Checksum = %d\n", checksum)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 9 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
