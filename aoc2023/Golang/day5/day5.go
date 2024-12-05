package aoc2023day5

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

var (
	initialSpans, processedSpans SpanList
)

var world [7]SpanList

func init() {
	initialSpans = createSpanList()
	processedSpans = createSpanList()

	for i := range world {
		world[i] = createSpanList()
	}
}

func Day(filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open file: %v\n", err)
		os.Exit(1)
	}
	defer file.Close()

	state := SEED
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		switch {
		case len(line) == 0:
			state++
		case state == SEED:
			fields := splitFields(line)[1:]
			for i, field := range fields {
				spanLength := parseInt(field)
				initialSpans = append(initialSpans,
					Span{spanLength, spanLength + 1, 0},
				)

				if isOdd(i) {
					processedSpans = append(processedSpans,
						Span{
							initialSpans[i-1].src,
							initialSpans[i-1].src + spanLength,
							0,
						},
					)
				}
			}
		case strings.Contains(line, ":"):
		default:
			fields := splitFields(line)
			world[state] = append(world[state],
				Span{
					parseInt(fields[1]),
					parseInt(fields[1]) + parseInt(fields[2]),
					parseInt(fields[0]),
				},
			)
		}
	}

	fmt.Println("Day 24 Results:")
	fmt.Println("Part 1:", findMinLocation(initialSpans))
	fmt.Println("Part 2:", findMinLocation(processedSpans))
}

func findMinLocation(spans SpanList) (minLocation int) {
	currentSpans, nextSpans := createSpanList(), createSpanList()

	push := func(s Span) {
		currentSpans = append(currentSpans, s)
	}

	pop := func() Span {
		i := len(currentSpans) - 1
		popped := currentSpans[i]
		currentSpans, currentSpans[i] = currentSpans[:i], Span{}
		return popped
	}

	minLocation = MaxInt
	for _, seed := range spans {
		currentSpans = currentSpans[:0]
		push(seed)

		for _, mapSpans := range world {
		SPLITMAP:
			for len(currentSpans) > 0 {
				br := pop()
				for _, mapSpan := range mapSpans {
					intersection := Span{
						max(mapSpan.src, br.src),
						min(mapSpan.end, br.end),
						0,
					}
					if intersection.src < intersection.end {
						offset := mapSpan.dst - mapSpan.src
						nextSpans = append(nextSpans, Span{intersection.src + offset, intersection.end + offset, 0})
						if br.src < intersection.src {
							push(Span{br.src, intersection.src, 0})
						}

						if intersection.end < br.end {
							push(Span{intersection.end, br.end, 0})
						}

						continue SPLITMAP
					}
				}
				nextSpans = append(nextSpans, br)
			}
			currentSpans, nextSpans = nextSpans, currentSpans
		}

		for _, span := range currentSpans {
			minLocation = min(minLocation, span.src)
		}
	}

	return
}

const (
	SEED = -1
	SIZE = 16
)

type Span struct {
	src, end, dst int
}

type SpanList []Span

func createSpanList() SpanList {
	return make(SpanList, 0, SIZE)
}

const MaxInt = int(^uint(0) >> 1)

var splitFields = strings.Fields

func isOdd(n int) bool {
	return n&1 > 0
}

func parseInt(s string) int {
	result := 0
	for i := range s {
		result = 10*result + int(s[i]-'0')
	}
	return result
}
