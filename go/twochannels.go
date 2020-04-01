package main

import "fmt"

func sum(s []int, c chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	c <- sum // send sum to c
}

func main() {
	s := []int{7, 2, 8, -9, 4, 0}

	// Using two channels
	c1 := make(chan int)
	c2 := make(chan int)

	go sum(s[:len(s)/2], c1) // 0 to half-1 -> 17
	go sum(s[len(s)/2:], c2) // half to end -> -5
	x, y := <-c1, <-c2       // receive from c (block until receive)

	fmt.Println(x, y, x+y) // Expect: 17, -5, 12
}
