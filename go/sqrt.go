package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64 {
	var z float64 = 1
	var prev float64
	for {
		z -= (z*z - x) / (2 * z)
		if float32(prev) == float32(z) {
			break
		}
		prev = z
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(math.Sqrt(2))
}
