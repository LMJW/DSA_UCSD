package main

import (
	"fmt"
	"testing"
)

func TestFastcount(t *testing.T) {
	var tcs = []struct {
		start  []int
		end    []int
		ps     []int
		result []int
	}{
		{
			start:  []int{0, 1, 2, 3},
			end:    []int{1, 2, 3, 4},
			ps:     []int{1, 2, 3, 4},
			result: []int{2, 2, 2, 1},
		},
		{
			start:  []int{0, 1, 2, 3},
			end:    []int{1, 2, 3, 4},
			ps:     []int{0, 4, 5},
			result: []int{1, 1, 0},
		},
		{
			start:  []int{0, 1, 2, 3},
			end:    []int{1, 2, 3, 4},
			ps:     []int{-1, 2, 5},
			result: []int{0, 2, 0},
		},
	}

	for _, tc := range tcs {
		r := fastcount(tc.start, tc.end, tc.ps)
		var flag bool
		for i := 0; i < len(r); i++ {
			if r[i] != tc.result[i] {
				flag = true
				fmt.Printf("Result miss match: %d - %d\n", r[i], tc.result[i])
			}
			if flag {
				fmt.Println(r, tc.result)
			}
		}
	}
}

func fastcount(s, e, p []int) []int {
	var vals [][2]int
	var res []int
	var hash = map[int]int{}
	for k := range s {
		vals = append(vals, [2]int{s[k], 1})
	}
	for k := range e {
		vals = append(vals, [2]int{e[k], -1})
	}
	for k := range p {
		vals = append(vals, [2]int{p[k], 0})
		hash[p[k]] = 0
	}

	var rec func([][2]int) [][2]int

	rec = func(x [][2]int) [][2]int {
		var t int
		if t = len(x); t <= 1 {
			return x
		}
		var rrr [][2]int
		// fmt.Println(t, t/2, x)
		l := rec(x[:t/2])
		// fmt.Println(">", x[:t/2])
		r := rec(x[t/2:])
		// fmt.Println("?", x[t/2:])
		var ll, lr, c = len(l), len(r), 0
		for i, j := 0, 0; c < ll+lr; c++ {
			if i < ll && j < lr {
				if l[i][0] < r[j][0] {
					rrr = append(rrr, l[i])
					i++
				} else if l[i][0] > r[j][0] {
					rrr = append(rrr, r[j])
					j++
				} else {
					if l[i][1] > r[j][1] {
						rrr = append(rrr, l[i])
						i++
					} else {
						// ignored the case of same point
						rrr = append(rrr, r[j])
						j++
					}
				}
			} else if i < ll {
				rrr = append(rrr, l[i])
				i++
			} else {
				rrr = append(rrr, r[j])
				j++
			}
		}
		return rrr
	}
	vals = rec(vals)
	// fmt.Println(vals)
	var mark int
	for i := 0; i < len(vals); i++ {
		mark += vals[i][1]
		if _, ok := hash[vals[i][0]]; vals[i][1] == 0 && ok {
			hash[vals[i][0]] = mark
		}
	}
	for _, v := range p {
		res = append(res, hash[v])
	}
	return res
}

func main() {}
