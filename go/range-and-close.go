package main

import (
	"fmt"
)

func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	//close(c)
}

func main() {
	c := make(chan int, 10)
	go fibonacci(cap(c), c)
	/*
		for i := range c {
			fmt.Println(i)
		}
	*/
	// We need to close channel in this case
	for i, n := 0, cap(c); i < n; i++ {
		fmt.Println(<-c)
	}
}
