package main

import (
	"io"

	"golang.org/x/tour/reader"
)

type MyReader struct{}

// TODO: Add a Read([]byte) (int, error) method to MyReader.
func (self MyReader) Read(b []byte) (int, error) {
	if len(b) <= 0 {
		return 0, io.EOF
	}
	var i int
	for i = 0; i < len(b); i += 1 {
		b[i] = 'A'
	}
	return i, nil
}

func main() {
	reader.Validate(MyReader{})
}
