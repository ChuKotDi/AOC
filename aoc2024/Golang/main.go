package main

import (
	aoc2024day1 "AOC/aoc2024/Golang/day1"
	aoc2024day2 "AOC/aoc2024/Golang/day2"
	aoc2024day3 "AOC/aoc2024/Golang/day3"
	"fmt"
)

func main() {
	fmt.Println("***   AOC 2024 (Golang)   ***")
	aoc2024day1.Day1("aoc2024/Golang/day1/part1_test.in", "aoc2024/Golang/day1/part2_test.in")
	aoc2024day2.Day2("aoc2024/Golang/day2/part1_test.in", "aoc2024/Golang/day2/part2_test.in")
	aoc2024day3.Day3("aoc2024/Golang/day3/part1_test.in", "aoc2024/Golang/day3/part2_test.in")
}
