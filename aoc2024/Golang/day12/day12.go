package aoc2024day12

import (
	"bufio"
	"fmt"
	"os"
)

func Day(filename string) {
	fmt.Println("Day 12 Results:")
	grid := readInput(filename)

	part1Sum, part2Sum := calculateResults(grid)

	fmt.Println("Part1: ", part1Sum)
	fmt.Println("Part2: ", part2Sum)
}

func readInput(filename string) [][]rune {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	grid := make([][]rune, 0)

	for scanner.Scan() {
		row := scanner.Text()
		grid = append(grid, []rune(row))
	}

	return grid
}

func calculateResults(grid [][]rune) (int, int) {
	part1Sum, part2Sum := 0, 0
	regions := findRegions(grid)

	for _, region := range regions {
		part1Sum += region.area * region.perimeter
		part2Sum += region.area * region.segmentCount
	}

	return part1Sum, part2Sum
}

type Region struct {
	area         int
	perimeter    int
	segmentCount int
}

type Coordinate struct {
	row, col int
}

func findRegions(grid [][]rune) []Region {
	rows, cols := len(grid), len(grid[0])
	visited := createVisitedGrid(rows, cols)
	var regions []Region

	for row := 0; row < rows; row++ {
		for col := 0; col < cols; col++ {
			if !visited[row][col] {
				regionCells := []Coordinate{}
				area, perimeter := exploreRegion(grid, visited, row, col, grid[row][col], &regionCells)
				segmentCount := countBoundarySegments(regionCells)
				regions = append(regions, Region{area, perimeter, segmentCount})
			}
		}
	}

	return regions
}

func createVisitedGrid(rows, cols int) [][]bool {
	visited := make([][]bool, rows)
	for i := range visited {
		visited[i] = make([]bool, cols)
	}
	return visited
}

func exploreRegion(grid [][]rune, visited [][]bool, row, col int, symbol rune, regionCells *[]Coordinate) (int, int) {
	rows, cols := len(grid), len(grid[0])
	if row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] != symbol {
		return 0, 1
	}

	if visited[row][col] {
		return 0, 0
	}

	visited[row][col] = true
	*regionCells = append(*regionCells, Coordinate{row, col})

	area, perimeter := 1, 0
	for _, direction := range directions {
		nextRow, nextCol := row+direction.row, col+direction.col
		additionalArea, additionalPerimeter := exploreRegion(grid, visited, nextRow, nextCol, symbol, regionCells)
		area += additionalArea
		perimeter += additionalPerimeter
	}

	return area, perimeter
}

func countBoundarySegments(regionCells []Coordinate) int {
	regionMap := make(map[Coordinate]bool, len(regionCells))
	for _, cell := range regionCells {
		regionMap[cell] = true
	}

	uniqueSegments := make(map[[4]int]bool, len(regionCells))
	for _, cell := range regionCells {
		for _, direction := range directions {
			next := Coordinate{cell.row + direction.row, cell.col + direction.col}

			if regionMap[next] {
				continue
			}

			currentRow, currentCol := cell.row, cell.col
			deltaRow, deltaCol := direction.row, direction.col

			for {
				if regionMap[Coordinate{currentRow + deltaCol, currentCol + deltaRow}] {
					if !regionMap[Coordinate{currentRow + deltaRow, currentCol + deltaCol}] {
						currentRow += deltaCol
						currentCol += deltaRow
						continue
					}
				}
				break
			}

			segmentKey := [4]int{currentRow, currentCol, deltaRow, deltaCol}
			uniqueSegments[segmentKey] = true
		}
	}

	return len(uniqueSegments)
}

var directions = []Coordinate{
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
}
