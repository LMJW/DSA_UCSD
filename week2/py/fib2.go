package main

import (
	"fmt"
)

func fib(n int) int64 {
	if n == 0 {
		return 0
	} else if n == 1 {
		return 1
	}
	var a, b int64
	a, b = 0, 1
	for i := 1; i < n-1; i++ {
		a, b = b, a+b
	}
	return b
}

func main() {
	var n int
	fmt.Scanln(&n)
	fmt.Println(fib(n) % 10)
}
