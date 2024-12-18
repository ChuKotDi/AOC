package aoc2024

import (
	aoc2024day1 "AOC/aoc2024/Golang/day1"
	aoc2024day10 "AOC/aoc2024/Golang/day10"
	aoc2024day11 "AOC/aoc2024/Golang/day11"
	aoc2024day12 "AOC/aoc2024/Golang/day12"
	aoc2024day13 "AOC/aoc2024/Golang/day13"
	aoc2024day16 "AOC/aoc2024/Golang/day16"
	aoc2024day17 "AOC/aoc2024/Golang/day17"
	aoc2024day18 "AOC/aoc2024/Golang/day18"
	aoc2024day2 "AOC/aoc2024/Golang/day2"
	aoc2024day3 "AOC/aoc2024/Golang/day3"
	aoc2024day4 "AOC/aoc2024/Golang/day4"
	aoc2024day5 "AOC/aoc2024/Golang/day5"
	aoc2024day6 "AOC/aoc2024/Golang/day6"
	aoc2024day7 "AOC/aoc2024/Golang/day7"
	aoc2024day8 "AOC/aoc2024/Golang/day8"
	aoc2024day9 "AOC/aoc2024/Golang/day9"
	"fmt"
)

func Run() {
	fmt.Println("***   AOC 2024 (Golang)   ***")
	aoc2024day1.Day("aoc2024/Golang/day1/part1_test.in", "aoc2024/Golang/day1/part2_test.in")
	aoc2024day2.Day("aoc2024/Golang/day2/part1_test.in", "aoc2024/Golang/day2/part2_test.in")
	aoc2024day3.Day("aoc2024/Golang/day3/part1_test.in", "aoc2024/Golang/day3/part2_test.in")
	aoc2024day4.Day("aoc2024/Golang/day4/part1_test.in", "aoc2024/Golang/day4/part2_test.in")
	aoc2024day5.Day("aoc2024/Golang/day5/part1_test.in", "aoc2024/Golang/day5/part2_test.in")
	aoc2024day6.Day("aoc2024/Golang/day6/part1_test.in", "aoc2024/Golang/day6/part2_test.in")
	aoc2024day7.Day("aoc2024/Golang/day7/part1_test.in", "aoc2024/Golang/day7/part2_test.in")
	aoc2024day8.Day("aoc2024/Golang/day8/part1_test.in", "aoc2024/Golang/day8/part2_test.in")
	aoc2024day9.Day("aoc2024/Golang/day9/part1_test.in", "aoc2024/Golang/day9/part2_test.in")
	aoc2024day10.Day("aoc2024/Golang/day10/part1_test.in", "aoc2024/Golang/day10/part2_test.in")
	aoc2024day11.Day("aoc2024/Golang/day11/part1_test.in", "aoc2024/Golang/day11/part2_test.in")
	aoc2024day12.Day("aoc2024/Golang/day12/part1_test.in")
	aoc2024day13.Day("aoc2024/Golang/day13/part1_test.in")

	aoc2024day16.Day("aoc2024/Golang/day16/part1_test.in")
	aoc2024day17.Day("aoc2024/Golang/day17/part1_test.in", "aoc2024/Golang/day17/part2_test.in")
	aoc2024day18.Day("aoc2024/Golang/day18/part1_test.in", "aoc2024/Golang/day18/part2_test.in", 7, 12)

	fmt.Println("*****************************")
	fmt.Println("")
}
