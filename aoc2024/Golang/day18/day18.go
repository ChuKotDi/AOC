package aoc2024day18

import (
	"container/list"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Point struct {
	x, y int
}

var directions = []Point{
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
}

func readFile(filename string) ([]Point, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var points []Point
	var line string
	for {
		_, err := fmt.Fscanf(file, "%s\n", &line)
		if err != nil {
			break
		}
		coords := strings.Split(line, ",")
		if len(coords) != 2 {
			continue
		}
		x, err := strconv.Atoi(coords[0])
		if err != nil {
			return nil, err
		}
		y, err := strconv.Atoi(coords[1])
		if err != nil {
			return nil, err
		}

		points = append(points, Point{x, y})
	}

	return points, nil
}

func inBounds(x, y, gridSize int) bool {
	return x >= 0 && y >= 0 && x < gridSize && y < gridSize
}

func findShortestPath(gridSize int, obstacles []Point, obstaclesCount int) int {
	grid := make([][]bool, gridSize)
	for i := range grid {
		grid[i] = make([]bool, gridSize)
	}

	for i := range obstacles {
		if i >= obstaclesCount {
			break
		}
		obs := obstacles[i]
		if inBounds(obs.x, obs.y, gridSize) {
			grid[obs.x][obs.y] = true
		}
	}

	queue := list.New()
	start := Point{0, 0}
	queue.PushBack(start)

	visited := make([][]bool, gridSize)
	for i := range visited {
		visited[i] = make([]bool, gridSize)
	}
	visited[start.x][start.y] = true

	steps := 0

	for queue.Len() > 0 {
		levelSize := queue.Len()
		for i := 0; i < levelSize; i++ {
			current := queue.Remove(queue.Front()).(Point)

			if current.x == gridSize-1 && current.y == gridSize-1 {
				return steps
			}

			for _, dir := range directions {
				newX, newY := current.x+dir.x, current.y+dir.y
				if inBounds(newX, newY, gridSize) && !visited[newX][newY] && !grid[newX][newY] {
					visited[newX][newY] = true
					queue.PushBack(Point{newX, newY})
				}
			}
		}
		steps++
	}

	return -1
}

func part1(filename string, gridSize int, obstaclesCount int) {
	fmt.Println("Part 1:")

	obstacles, err := readFile(filename)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	result := findShortestPath(gridSize, obstacles, obstaclesCount)
	fmt.Println("Minimal steps to exit =", result)
}

func part2(filename string, gridSize int, obstaclesCount int) {
	fmt.Println("Part 2:")

	obstacles, err := readFile(filename)
	if err != nil {
		fmt.Println("Error reading file:", err)
		return
	}

	for i := obstaclesCount; i <= len(obstacles); i++ {
		result := findShortestPath(gridSize, obstacles, i)
		if result == -1 {
			obs := obstacles[i-1]
			fmt.Printf("No path exists after %d obstacles with (%d,%d)\n", i, obs.x, obs.y)
			break
		}
	}
}

func Day(filenamePart1, filenamePart2 string, gridSize int, obstaclesCount int) {
	fmt.Println("Day 18 Results:")
	part1(filenamePart1, gridSize, obstaclesCount)
	part2(filenamePart2, gridSize, obstaclesCount)
}
