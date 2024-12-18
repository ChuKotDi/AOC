package aoc2024day16

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
	"slices"
	"strings"
	"sync"
)

const MAXDIM = 142

type Cell struct {
	r, c, dir int
}

type State struct {
	Cell
	dist int
}

type MinHeap []State

type Maze struct {
	dist1 []int
	dist2 []int
	tiles map[int]struct{}
	data  []string
	start Cell
	goal  Cell
	best  int
}

var DIRECTIONS = [4]Cell{{-1, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, -1, 0}}

func key(x Cell) int {
	return x.r*MAXDIM*4 + x.c*4 + x.dir
}

func (m Maze) forwardSearch() Maze {
	H, W := len(m.data), len(m.data[0])

	var pq MinHeap
	heap.Push(&pq, State{Cell{r: m.start.r, c: m.start.c, dir: 0}, 0})

	best := 0
	dist := make([]int, MAXDIM*MAXDIM*4)
	visited := make([]bool, MAXDIM*MAXDIM*4)

	for pq.Len() > 0 {
		cur := heap.Pop(&pq).(State)

		if visited[key(cur.Cell)] {
			continue
		}

		visited[key(cur.Cell)] = true

		if dist[key(cur.Cell)] == 0 {
			dist[key(cur.Cell)] = cur.dist
		}

		if cur.r == m.goal.r && cur.c == m.goal.c && best == 0 {
			best = cur.dist
		}

		δr, δc := DIRECTIONS[cur.dir].r, DIRECTIONS[cur.dir].c
		rr, cc := cur.r+δr, cur.c+δc
		if rr >= 0 && rr < H && cc >= 0 && cc < W && m.data[rr][cc] != '#' {
			heap.Push(&pq, State{Cell{r: rr, c: cc, dir: cur.dir}, cur.dist + 1})
		}

		heap.Push(&pq, State{Cell{r: cur.r, c: cur.c, dir: (cur.dir + 1) % 4}, cur.dist + 1000})
		heap.Push(&pq, State{Cell{r: cur.r, c: cur.c, dir: (cur.dir + 3) % 4}, cur.dist + 1000})
	}

	m.best = best
	m.dist1 = dist

	return m
}

func (m Maze) backwardSearch() Maze {
	H, W := len(m.data), len(m.data[0])
	var pq MinHeap

	for dir := range DIRECTIONS {
		heap.Push(&pq, State{Cell{r: m.goal.r, c: m.goal.c, dir: dir}, 0})
	}

	dist := make([]int, MAXDIM*MAXDIM*4)
	visited := make([]bool, MAXDIM*MAXDIM*4)

	for pq.Len() > 0 {
		cur := heap.Pop(&pq).(State)

		if visited[key(cur.Cell)] {
			continue
		}

		visited[key(cur.Cell)] = true

		if dist[key(cur.Cell)] == 0 {
			dist[key(cur.Cell)] = cur.dist
		}

		δr, δc := DIRECTIONS[(cur.dir+2)%4].r, DIRECTIONS[(cur.dir+2)%4].c
		rr, cc := cur.r+δr, cur.c+δc
		if rr >= 0 && rr < H && cc >= 0 && cc < W && m.data[rr][cc] != '#' {
			heap.Push(&pq, State{Cell{r: rr, c: cc, dir: cur.dir}, cur.dist + 1})
		}

		heap.Push(&pq, State{Cell{r: cur.r, c: cur.c, dir: (cur.dir + 1) % 4}, cur.dist + 1000})
		heap.Push(&pq, State{Cell{r: cur.r, c: cur.c, dir: (cur.dir + 3) % 4}, cur.dist + 1000})
	}

	m.dist2 = dist

	return m
}

func (m Maze) solve() (int, []int) {
	var wg sync.WaitGroup
	var m1, m2 Maze

	wg.Add(1)
	go func() {
		defer wg.Done()
		m1 = m.forwardSearch()
	}()

	m2 = m.backwardSearch()
	wg.Wait()

	best, d1, d2 := m1.best, m1.dist1, m2.dist2
	tiles := make([]int, 0, 602)

	for i := range d1 {
		if d1[i]+d2[i] == best {
			i := i >> 2
			tiles = append(tiles, i)
		}
	}

	slices.Sort(tiles)
	return best + 1000, slices.Compact(tiles)
}

func (h MinHeap) Len() int           { return len(h) }
func (h MinHeap) Less(i, j int) bool { return h[i].dist < h[j].dist }
func (h MinHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *MinHeap) Push(x interface{}) {
	*h = append(*h, x.(State))
}

func (h *MinHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func readMazeData(input *os.File) ([]string, Cell, Cell) {
	var start, goal Cell
	data := make([]string, 0, MAXDIM)

	scanner := bufio.NewScanner(input)
	for scanner.Scan() {
		line := scanner.Text()

		if i := strings.Index(line, "S"); i >= 0 {
			start = Cell{len(data), i, 0}
		}
		if i := strings.Index(line, "E"); i >= 0 {
			goal = Cell{len(data), i, 0}
		}
		data = append(data, line)
	}

	return data, start, goal
}

func Day(filename string) {
	fmt.Println("Day 16 Results:")
	file, err := os.Open(filename)
	if err != nil {
		return
	}
	defer file.Close()

	data, start, goal := readMazeData(file)

	maze := Maze{data: data, start: start, goal: goal}
	score, tiles := maze.solve()

	fmt.Println("Part1:", score)
	fmt.Println("Part2:", len(tiles))
}
