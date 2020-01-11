package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	var idx int
	ret := make(map[int]int)
	return func() int {
		switch idx++; idx {
		case 1:
			ret[idx] = 0
		case 2:
			ret[idx] = 1
		default:
			ret[idx] = ret[idx-1] + ret[idx-2]
		}
		return ret[idx]
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
