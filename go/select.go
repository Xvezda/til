package main

import "fmt"

func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
		case c <- x: // Send x to channel
			x, y = y, x+y
		case <-quit: // Blocking continues until quit channel got something
			fmt.Println("quit")
			return
		}
	}
}

func main() {
	c := make(chan int)
	quit := make(chan int)
	go func() { // It will run on thread
		for i := 0; i < 10; i++ {
			fmt.Println(<-c) // Blocking until fibonacci send x to channel
		}
		quit <- 0 // Send 0 to quit
	}()
	fibonacci(c, quit)
}
