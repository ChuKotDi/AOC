package aoc2023day4

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func Day(filename string) {
	fmt.Println("Day 4 Results:")
	const MAXMATCH = 16
	score, ncard := 0, 0

	deck := make([]int, MAXMATCH)
	θ := func(i int) int {
		return i & (MAXMATCH - 1)
	}

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Error opening the file:", err)
		return
	}
	defer file.Close()

	input := bufio.NewScanner(file)
	for i := 0; input.Scan(); i++ {
		inputText := input.Text()

		raw := split(inputText[index(inputText, ":")+1:], " | ")
		w, card := fields(raw[0]), fields(raw[1])

		wins := nullset
		for i := range w {
			wins.set(atoi(w[i]))
		}

		nmatch := 0
		for i := range card {
			if wins.get(atoi(card[i])) > 0 {
				nmatch++
			}
		}

		score += 1 << nmatch >> 1

		deck[θ(i)] += 1
		for ii := i + 1; ii < (i+1)+nmatch; ii++ {
			deck[θ(ii)] += deck[θ(i)]
		}

		ncard += deck[θ(i)]
		deck[θ(i)] = 0
	}

	if err := input.Err(); err != nil {
		fmt.Println("Error reading the file:", err)
		return
	}

	fmt.Println("Part 1: score =", score)
	fmt.Println("Part 2: ncard =", ncard)
}

var fields, index, split = strings.Fields, strings.Index, strings.Split

const uint128size = 128

type uint128 struct {
	w0, w1 uint64
}

var (
	zero128 uint128
	nullset = zero128
)

func (u *uint128) set(n int) {
	switch n >> 6 {
	case 1:
		u.w1 |= (1 << (n & 0x3f))
	case 0:
		u.w0 |= (1 << (n & 0x3f))
	}
}

func (u *uint128) get(n int) uint64 {
	x := u.rsh(n)
	return x.w0 & 1
}

func (u uint128) rsh(n int) uint128 {
	var a uint64

	switch {
	case n > 128:
		return zero128
	case n > 64:
		u.w1, u.w0 = 0, u.w1
		n -= 64
		goto sh64
	}

	a = u.w1 << (64 - n)
	u.w1 = u.w1 >> n

sh64:
	u.w0 = (u.w0 >> n) | a

	return u
}

func atoi(s string) (n int) {
	for i := range s {
		n = 10*n + int(s[i]-'0')
	}
	return
}
