package aoc2024day17

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strings"
)

type Machine struct {
	out []int
	ra  int
	rb  int
	rc  int
	pc  int
}

func (m *Machine) exec(text []int) {
	combo := func(arg int) int {
		return []int{
			0: 0, 1: 1, 2: 2, 3: 3,
			A: m.ra,
			B: m.rb,
			C: m.rc,
		}[arg]
	}

	for m.pc < len(text) {
		op, arg := text[m.pc], text[m.pc+1]
		decode := map[int]func(){
			ADV: func() { m.ra >>= combo(arg) },
			BXL: func() { m.rb ^= arg },
			BST: func() { m.rb = combo(arg) & 0x7 },
			BXC: func() { m.rb ^= m.rc },
			OUT: func() { m.out = append(m.out, combo(arg)&0x7) },
			BDV: func() { m.rb = m.ra >> combo(arg) },
			CDV: func() { m.rc = m.ra >> combo(arg) },
			JNZ: func() {
				if m.ra != 0 {
					m.pc = arg - 2
				}
			},
		}

		decode[op]()
		m.pc += 2
	}
}

func (m *Machine) quine(text []int) int {
	table := make([]int, 0)
	for a := 0; a < (1 << 10); a++ {
		table = append(table, m.init(a, 0, 0).execAndGetOut(text)[0])
	}

	cur := make([][]int, 0, len(table))
	for i, val := range table {
		if val == text[0] {
			cur = append(cur, []int{i})
		}
	}

	var nxt [][]int
	for _, word := range text[1:] {
		nxt = make([][]int, 0, len(cur))
		for _, x := range cur {
			seed := x[len(x)-1] >> 3
			for i := 0; i < 8; i++ {
				if table[(i<<7)+seed] == word {
					nxt = append(nxt, append(slices.Clone(x), (i<<7)+seed))
				}
			}
		}
		cur = nxt
	}

	pack := func(x []int) int {
		i, d := x[0], 10
		for _, c := range x[1:] {
			i += (c >> 7) << d
			d += 3
		}
		return i
	}

	for _, x := range cur {
		a := pack(x)
		if slices.Equal(text, m.init(a, 0, 0).execAndGetOut(text)) {
			return a
		}
	}

	panic("unreachable")
}

const MaxInf = int(^uint(0) >> 1)

func (m *Machine) init(a, b, c int) *Machine {
	m.ra, m.rb, m.rc = a, b, c
	m.pc = 0
	m.out = []int{}
	return m
}

func (m *Machine) execAndGetOut(text []int) []int {
	m.exec(text)
	return m.out
}

const (
	A = iota + 4
	B
	C
	NIL
)

const (
	ADV = iota
	BXL
	BST
	JNZ
	BXC
	OUT
	BDV
	CDV
)

var code = []string{
	ADV: "ADV",
	BXL: "BXL",
	BST: "BST",
	JNZ: "JNZ",
	BXC: "BXC",
	OUT: "OUT",
	BDV: "BDV",
	CDV: "CDV",
}

var regname = []string{
	0:   "0",
	1:   "1",
	2:   "2",
	3:   "3",
	A:   "A",
	B:   "B",
	C:   "C",
	NIL: "?",
}

func (m *Machine) String() string {
	return strings.Trim(strings.Replace(fmt.Sprint(m.out), " ", ",", -1), "[]")
}

func atoi(s string) (n int) {
	for i := range s {
		n = 10*n + int(s[i]-'0')
	}
	return
}

func readFile(filename string) (*Machine, []int) {
	var mach Machine
	var prog []int
	file, err := os.Open(filename)
	if err != nil {
		return &mach, prog
	}
	defer file.Close()

	var reg byte
	var val int

	input := bufio.NewScanner(file)
	for input.Scan() {
		line := input.Text()
		switch {
		case len(line) == 0:
		case line[0] == 'R':
			reg, val = line[9], atoi(line[12:])
			switch reg {
			case 'A':
				mach.ra = val
			case 'B':
				mach.rb = val
			case 'C':
				mach.rc = val
			}
		case line[0] == 'P':
			text := strings.Split(line[9:], ",")
			prog = make([]int, len(text))
			for i, word := range text {
				prog[i] = atoi(word)
			}
		}
	}

	return &mach, prog
}

func part1(filename string) {
	fmt.Println("Part 1:")

	mach, prog := readFile(filename)
	mach.exec(prog)
	fmt.Println(mach)
}

func part2(filename string) {
	fmt.Println("Part 2:")
	mach, prog := readFile(filename)
	fmt.Println(mach.quine(prog))
}

func Day(filenamePart1, filenamePart2 string) {
	fmt.Println("Day 17 Results:")
	part1(filenamePart1)
	part2(filenamePart2)
}
