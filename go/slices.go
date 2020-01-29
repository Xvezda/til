package main

import "golang.org/x/tour/pic"

func Fill(img [][]uint8) {
	var v uint8
	for i := 0; i < len(img); i += 1 {
		for j := 0; j < len(img[i]); j += 1 {
			img[i][j] = v
			v += 1
		}
	}
}

func Pic(dx, dy int) [][]uint8 {
	img := make([][]uint8, dy)
	for i := 0; i < dy; i += 1 {
		img[i] = make([]uint8, dx)
	}
	Fill(img)

	return img
}

func main() {
	pic.Show(Pic)
}
