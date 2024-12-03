package Golang

import (
	aoc2023day1 "AOC/aoc2023/Golang/day1"
	aoc2023day2 "AOC/aoc2023/Golang/day2"
	aoc2023day24 "AOC/aoc2023/Golang/day24"
	"fmt"
)

func Run() {
	fmt.Println("***   AOC 2023 (Golang)   ***")
	aoc2023day1.Day("aoc2023/Golang/day1/part1_test.in", "aoc2023/Golang/day1/part2_test.in")
	aoc2023day2.Day("aoc2023/Golang/day2/part1_test.in", "aoc2023/Golang/day2/part2_test.in")
	aoc2023day24.Day("aoc2023/Golang/day24/part1_test.in", "aoc2023/Golang/day24/part2_test.in")

	fmt.Println("*****************************")
	fmt.Println("")
}
