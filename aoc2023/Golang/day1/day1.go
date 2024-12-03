package aoc2023day1

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func part1(filename string) {
	sum1 := 0
	file, err := os.Open(filename) // Открываем файл для чтения
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close() // Закрываем файл после обработки

	input := bufio.NewScanner(file)
	for input.Scan() {
		line := input.Text()
		sum1 += stoi(line, DigitsOnly)
	}
	if err := input.Err(); err != nil {
		fmt.Println("Error reading file:", err)
	}
	fmt.Println("Part 1: sum =", sum1)
}

func part2(filename string) {
	sum2 := 0
	file, err := os.Open(filename) // Открываем файл для чтения
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer file.Close() // Закрываем файл после обработки

	input := bufio.NewScanner(file)
	for input.Scan() {
		line := input.Text()
		sum2 += stoi(line, TextAndDigits)
	}
	if err := input.Err(); err != nil {
		fmt.Println("Error reading file:", err)
	}
	fmt.Println("Part 2: sum =", sum2)
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 1 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}

const (
	DigitsOnly    = false
	TextAndDigits = !DigitsOnly
)

func stoi(s string, mode bool) int {
	trie := digits
	if mode == TextAndDigits {
		trie = texts
	}
	l, r := 0, 0
	for i := range s {
		if nodes := trie[s[i]]; l == 0 && len(nodes) > 0 {
			for k := range nodes {
				if nodes[k].match(s[i+1:], LR) {
					l = nodes[k].atoi()
					break
				}
			}
		}

		j := (len(s) - 1) - i
		if nodes := trie[s[j]]; r == 0 && len(nodes) > 0 {
			for k := range nodes {
				if nodes[k].match(s[:j], RL) {
					r = nodes[k].atoi()
					break
				}
			}
		}

		if l*r > 0 {
			return 10*l + r
		}
	}

	panic("unreachable")
}

type trie [][]node

const (
	LR = false
	RL = !LR
)

type node struct {
	trans string
	state int
}

func (n node) match(s string, dir bool) bool {
	match := strings.HasPrefix
	if dir == RL {
		match = strings.HasSuffix
	}
	return match(s, n.trans)
}

func (n node) atoi() int {
	return n.state
}

const ε = ""

var digits = trie{
	'1': {{ε, 1}}, '2': {{ε, 2}}, '3': {{ε, 3}}, '4': {{ε, 4}}, '5': {{ε, 5}},
	'6': {{ε, 6}}, '7': {{ε, 7}}, '8': {{ε, 8}}, '9': {{ε, 9}}, 'z': {},
}

var texts = trie{
	'1': {{ε, 1}}, '2': {{ε, 2}}, '3': {{ε, 3}}, '4': {{ε, 4}}, '5': {{ε, 5}},
	'6': {{ε, 6}}, '7': {{ε, 7}}, '8': {{ε, 8}}, '9': {{ε, 9}}, 'z': {},

	'e': {{"ight", 8}, {"on", 1}, {"thre", 3}, {"fiv", 5}, {"nin", 9}},
	'f': {{"ive", 5}, {"our", 4}},
	'n': {{"ine", 9}, {"seve", 7}},
	'o': {{"ne", 1}, {"tw", 2}},
	'r': {{"fou", 4}},
	's': {{"even", 7}, {"ix", 6}},
	't': {{"hree", 3}, {"wo", 2}, {"eigh", 8}},
	'x': {{"si", 6}},
}
