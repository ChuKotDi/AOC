package aoc2024

import (
	aoc2024day1 "AOC/aoc2024/Golang/day1"
	aoc2024day2 "AOC/aoc2024/Golang/day2"
	aoc2024day3 "AOC/aoc2024/Golang/day3"
	aoc2024day4 "AOC/aoc2024/Golang/day4"
	aoc2024day5 "AOC/aoc2024/Golang/day5"
	"fmt"
)

func Run() {
	fmt.Println("***   AOC 2024 (Golang)   ***")
	aoc2024day1.Day("aoc2024/Golang/day1/part1_test.in", "aoc2024/Golang/day1/part2_test.in")
	aoc2024day2.Day("aoc2024/Golang/day2/part1_test.in", "aoc2024/Golang/day2/part2_test.in")
	aoc2024day3.Day("aoc2024/Golang/day3/part1_test.in", "aoc2024/Golang/day3/part2_test.in")
	aoc2024day4.Day("aoc2024/Golang/day4/part1_test.in", "aoc2024/Golang/day4/part2_test.in")
	aoc2024day5.Day("aoc2024/Golang/day5/part1_test.in", "aoc2024/Golang/day5/part2_test.in")

	fmt.Println("*****************************")
	fmt.Println("")
}
