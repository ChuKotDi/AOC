package aoc2024day5

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rule struct {
	X, Y int
}

func ParseInput(filename string) ([]Rule, [][]int) {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var rules []Rule
	var updates [][]int
	scanner := bufio.NewScanner(file)
	section := 1

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			section = 2
			continue
		}

		if section == 1 {
			parts := strings.Split(line, "|")
			x, _ := strconv.Atoi(parts[0])
			y, _ := strconv.Atoi(parts[1])
			rules = append(rules, Rule{X: x, Y: y})
		} else {
			parts := strings.Split(line, ",")
			var update []int
			for _, p := range parts {
				num, _ := strconv.Atoi(p)
				update = append(update, num)
			}
			updates = append(updates, update)
		}
	}

	return rules, updates
}

func IsUpdateValid(update []int, rules []Rule) bool {
	indexMap := make(map[int]int)
	for i, page := range update {
		indexMap[page] = i
	}

	for _, rule := range rules {
		xIndex, xExists := indexMap[rule.X]
		yIndex, yExists := indexMap[rule.Y]
		if xExists && yExists && xIndex > yIndex {
			return false
		}
	}
	return true
}

func MiddlePage(update []int) int {
	return update[len(update)/2]
}

func part1(filename string) {
	rules, updates := ParseInput(filename)

	sum := 0
	for _, update := range updates {
		if IsUpdateValid(update, rules) {
			sum += MiddlePage(update)
		}
	}
	fmt.Println("Part1: sum =", sum)
}

func OrderUpdate(update []int, rules []Rule) []int {
	dependencies := make(map[int][]int)
	inDegree := make(map[int]int)

	for _, page := range update {
		dependencies[page] = []int{}
		inDegree[page] = 0
	}

	for _, rule := range rules {
		if contains(update, rule.X) && contains(update, rule.Y) {
			dependencies[rule.X] = append(dependencies[rule.X], rule.Y)
			inDegree[rule.Y]++
		}
	}

	var sorted []int
	var queue []int

	for page, degree := range inDegree {
		if degree == 0 {
			queue = append(queue, page)
		}
	}

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]
		sorted = append(sorted, current)

		for _, neighbor := range dependencies[current] {
			inDegree[neighbor]--
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}

	return sorted
}

func contains(slice []int, value int) bool {
	for _, v := range slice {
		if v == value {
			return true
		}
	}
	return false
}

func part2(filename string) {
	rules, updates := ParseInput(filename)

	sum := 0
	for _, update := range updates {
		if !IsUpdateValid(update, rules) {
			orderedUpdate := OrderUpdate(update, rules)
			sum += MiddlePage(orderedUpdate)
		}
	}
	fmt.Println("Part2: sum =", sum)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 5 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
