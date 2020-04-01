package main

import "fmt"

func main() {
	ch := make(chan string, 10)
	go func() {
		// defer close(ch)
		// Send 3 messages
		// With out closing
		ch <- "do something"
		ch <- "and then something"
		ch <- "finish"
	}()

	// Explicitly match send, receive count
	// Get 3 messages
	for i := 0; i < 3; i += 1 {
		task := <-ch
		fmt.Println(task)
	}
}
