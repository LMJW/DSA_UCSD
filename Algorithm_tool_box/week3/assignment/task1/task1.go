package main

import (
	"fmt"
)

func minchange(x int) int {
	var count int
	var d = []int{10, 5, 1}
	var i int
	for x != 0 {
		for x >= d[i] {
			x -= d[i]
			count++
		}
		i++
	}
	return count
}

func main() {
	var n int
	fmt.Scanln(&n)
	fmt.Println(minchange(n))
}
