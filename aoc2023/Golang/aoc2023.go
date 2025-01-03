package Golang

import (
	aoc2023day1 "AOC/aoc2023/Golang/day1"
	aoc2023day2 "AOC/aoc2023/Golang/day2"
	aoc2023day24 "AOC/aoc2023/Golang/day24"
	aoc2023day3 "AOC/aoc2023/Golang/day3"
	aoc2023day4 "AOC/aoc2023/Golang/day4"
	aoc2023day5 "AOC/aoc2023/Golang/day5"
	aoc2023day6 "AOC/aoc2023/Golang/day6"
	"fmt"
)

func Run() {
	fmt.Println("***   AOC 2023 (Golang)   ***")
	aoc2023day1.Day("aoc2023/Golang/day1/part1_test.in", "aoc2023/Golang/day1/part2_test.in")
	aoc2023day2.Day("aoc2023/Golang/day2/part1_test.in", "aoc2023/Golang/day2/part2_test.in")
	aoc2023day3.Day("aoc2023/Golang/day3/part1_test.in", "aoc2023/Golang/day3/part2_test.in")
	aoc2023day4.Day("aoc2023/Golang/day4/part1_test.in")
	aoc2023day5.Day("aoc2023/Golang/day5/part1_test.in")
	aoc2023day6.Day("aoc2023/Golang/day6/part1_test.in")
	aoc2023day24.Day("aoc2023/Golang/day24/part1_test.in", "aoc2023/Golang/day24/part2_test.in")

	fmt.Println("*****************************")
	fmt.Println("")
}
