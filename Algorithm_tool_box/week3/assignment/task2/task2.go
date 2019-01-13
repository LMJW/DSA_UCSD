package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

func fitbag() {}

func readline(r *bufio.Reader) (int, int) {
	v, _, _ := r.ReadLine()
	var s = string(v)
	var ss = strings.Split(s, " ")
	var i, _ = strconv.Atoi(ss[0])
	var j, _ = strconv.Atoi(ss[1])
	return i, j
}

func main() {
	var scanner = bufio.NewReader(os.Stdin)
	var n, bag = readline(scanner)
	for i := 0; i < n; i++ {
		sort.Ints()
	}
}
