package aoc2024day4

import (
	"bufio"
	"fmt"
	"os"
)

var directions = [][]int{
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0},
	{1, 1},
	{1, -1},
	{-1, 1},
	{-1, -1},
}

func countXMAS(grid [][]rune) int {
	word := "XMAS"
	wordLen := len(word)
	rows := len(grid)
	cols := len(grid[0])
	count := 0

	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			for _, d := range directions {
				found := true
				for k := 0; k < wordLen; k++ {
					nr := r + k*d[0]
					nc := c + k*d[1]
					if nr < 0 || nc < 0 || nr >= rows || nc >= cols || grid[nr][nc] != rune(word[k]) {
						found = false
						break
					}
				}
				if found {
					count++
				}
			}
		}
	}

	return count
}

func readGridFromFile(filename string) [][]rune {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var grid [][]rune
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		grid = append(grid, []rune(line))
	}

	if err := scanner.Err(); err != nil {
		panic(err)
	}

	return grid
}

func part1(filename string) {
	grid := readGridFromFile(filename)
	result := countXMAS(grid)
	fmt.Printf("Part1: XMAS appears %d times\n", result)
}

func countXMASX(grid [][]rune) int {
	rows := len(grid)
	cols := len(grid[0])
	count := 0

	for r := 1; r < rows-1; r++ {
		for c := 1; c < cols-1; c++ {
			if grid[r][c] == 'A' {
				if isValidXMAS(grid, r, c) {
					count++
				}
			}
		}
	}

	return count
}

func isValidXMAS(grid [][]rune, r, c int) bool {
	tl := grid[r-1][c-1] == 'M' && grid[r+1][c+1] == 'S'
	tr := grid[r-1][c+1] == 'M' && grid[r+1][c-1] == 'S'
	bl := grid[r+1][c-1] == 'M' && grid[r-1][c+1] == 'S'
	br := grid[r+1][c+1] == 'M' && grid[r-1][c-1] == 'S'

	/*
		 tl c-1  c  c+1 tr
		r-1 []   []  []
		r   []   []  []
		r+1 []   []  []
		 bl				br
	*/
	return (tl && tr) || (tr && br) || (br && bl) || (bl && tl)
}

func part2(filename string) {
	grid := readGridFromFile(filename)
	result := countXMASX(grid)
	fmt.Printf("Part2: X-MAS appears %d times\n", result)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 4 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
