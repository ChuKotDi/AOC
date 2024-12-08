package aoc2024day8

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

func readMap(filename string) [][]rune {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer func(file *os.File) {
		err := file.Close()
		if err != nil {

		}
	}(file)

	var grid [][]rune
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		grid = append(grid, []rune(scanner.Text()))
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}
	return grid
}

func getAntennaPositions(grid [][]rune) map[rune][][2]int {
	rows := len(grid)
	cols := len(grid[0])

	antennas := make(map[rune][][2]int)
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			if grid[r][c] != '.' {
				antennas[grid[r][c]] = append(antennas[grid[r][c]], [2]int{r, c})
			}
		}
	}
	return antennas
}

func absGCD(a, b int) int {
	if b == 0 {
		return int(math.Abs(float64(a)))
	}
	return absGCD(b, a%b)
}

func addAntinode(antinodes map[[2]int]bool, pos [2]int, grid [][]rune) {
	rows := len(grid)
	cols := len(grid[0])

	if pos[0] >= 0 && pos[0] < rows && pos[1] >= 0 && pos[1] < cols {
		antinodes[pos] = true
	}
}

func calculateAntinodes(grid [][]rune) int {
	antennas := getAntennaPositions(grid)

	antinodes := make(map[[2]int]bool)
	for _, positions := range antennas {
		for i := 0; i < len(positions); i++ {
			for j := 0; j < len(positions); j++ {
				if i == j {
					continue
				}

				p1, p2 := positions[i], positions[j]
				dr := p2[0] - p1[0]
				dc := p2[1] - p1[1]

				mid := [2]int{p1[0] - dr, p1[1] - dc}
				far := [2]int{p1[0] + 2*dr, p1[1] + 2*dc}

				addAntinode(antinodes, mid, grid)
				addAntinode(antinodes, far, grid)
			}
		}
	}

	return len(antinodes)
}

func calculateAntinodesPart2WithGrid(grid [][]rune) (int, [][]rune) {
	antennas := getAntennaPositions(grid)

	antinodes := make(map[[2]int]bool)
	for _, positions := range antennas {
		if len(positions) > 1 {
			for _, pos := range positions {
				antinodes[pos] = true
			}

			for i := 0; i < len(positions); i++ {
				for j := i + 1; j < len(positions); j++ {
					p1, p2 := positions[i], positions[j]
					dr := p2[0] - p1[0]
					dc := p2[1] - p1[1]
					gcd := absGCD(dr, dc)

					stepR := dr / gcd
					stepC := dc / gcd

					curr := p1
					for {
						curr = [2]int{curr[0] + stepR, curr[1] + stepC}
						if curr[0] < 0 || curr[0] >= len(grid) || curr[1] < 0 || curr[1] >= len(grid[0]) {
							break
						}
						antinodes[curr] = true
					}

					curr = p2
					for {
						curr = [2]int{curr[0] - stepR, curr[1] - stepC}
						if curr[0] < 0 || curr[0] >= len(grid) || curr[1] < 0 || curr[1] >= len(grid[0]) {
							break
						}
						antinodes[curr] = true
					}
				}
			}
		}
	}

	visualGrid := make([][]rune, len(grid))
	for r := range grid {
		visualGrid[r] = make([]rune, len(grid[0]))
		copy(visualGrid[r], grid[r])
	}

	for pos := range antinodes {
		if visualGrid[pos[0]][pos[1]] == '.' {
			visualGrid[pos[0]][pos[1]] = '#'
		}
	}

	return len(antinodes), visualGrid
}

func printGrid(grid [][]rune) {
	for _, row := range grid {
		fmt.Println(string(row))
	}
}

func part1(filename string) {
	grid := readMap(filename)
	result := calculateAntinodes(grid)
	fmt.Printf("Part 1: %d\n", result)
}

func part2(filename string) {
	grid := readMap(filename)
	count, visualGrid := calculateAntinodesPart2WithGrid(grid)
	fmt.Printf("Part 2: %d\n", count)
	fmt.Println("Visualized Grid:")
	printGrid(visualGrid)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 8 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
