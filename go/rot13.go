package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (self *rot13Reader) Read(b []byte) (int, error) {
	n, err := self.r.Read(b)
	for i := 0; i < n; i += 1 {
		switch {
		case 'a' <= b[i] && b[i] <= 'z':
			b[i] = (b[i]-'a'+13)%('z'-'a'+1) + 'a'
		case 'A' <= b[i] && b[i] <= 'Z':
			b[i] = (b[i]-'A'+13)%('Z'-'A'+1) + 'A'
		default:
		}
	}
	return n, err
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
