package main

import "fmt"

func main() {
	ch := make(chan string, 10)
	go func() {
		defer close(ch)
		ch <- "do something"
		ch <- "and then something"
		ch <- "finish"
	}()

	for task := range ch {
		fmt.Println(task)
	}
}
