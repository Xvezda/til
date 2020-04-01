package main

import "fmt"

func main() {
	// Array
	a1 := [3]int{1, 2, 3}
	a2 := [...]int{1, 2, 3}

	// Slices
	s1 := []int{1, 2, 3}
	s2 := a1[:]

	fmt.Println(a1, a2)
	fmt.Println(s1, s2)
}
