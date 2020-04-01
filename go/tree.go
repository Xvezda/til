package main

import (
	"fmt"

	"golang.org/x/tour/tree"
)

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {
	WalkRecursive(t, ch)
	close(ch)
}

func WalkRecursive(t *tree.Tree, ch chan int) {
	if t != nil {
		WalkRecursive(t.Left, ch)
		ch <- t.Value
		WalkRecursive(t.Right, ch)
	}
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
	ch1, ch2 := make(chan int), make(chan int)
	go Walk(t1, ch1)
	go Walk(t2, ch2)
	for {
		n1, ok1 := <-ch1
		n2, ok2 := <-ch2
		if ok1 != ok2 || n1 != n2 {
			return false
		}
		if !ok1 {
			break
		}
	}
	return true

}

func main() {
	ch := make(chan int)
	go Walk(tree.New(1), ch)
	fmt.Println(Same(tree.New(1), tree.New(2)))
	fmt.Println(Same(tree.New(1), tree.New(1)))
	fmt.Println(Same(tree.New(2), tree.New(1)))

}
