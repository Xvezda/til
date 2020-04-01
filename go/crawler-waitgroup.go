package main

// https://gist.github.com/harryhare/6a4979aa7f8b90db6cbc74400d0beb49#gistcomment-2934997
import (
	"fmt"
	// No longer needed for sleeping.
	//"time"
	"sync"
)

type Fetcher interface {
	// Fetch returns the body of URL and
	// a slice of URLs found on that page.
	Fetch(url string) (body string, urls []string, err error)
}
type SafeCounter struct {
	v   map[string]bool
	mux sync.Mutex
	wg  sync.WaitGroup
}

var c SafeCounter = SafeCounter{v: make(map[string]bool)}

func (s SafeCounter) checkvisited(url string) bool {
	s.mux.Lock()
	defer s.mux.Unlock()
	_, ok := s.v[url]
	if ok == false {
		s.v[url] = true
		return false
	}
	return true

}

// Crawl uses fetcher to recursively crawl
// pages starting with url, to a maximum of depth.
func Crawl(url string, depth int, fetcher Fetcher) {
	// TODO: Fetch URLs in parallel.
	// TODO: Don't fetch the same URL twice.
	// This implementation doesn't do either:
	defer c.wg.Done()
	if depth <= 0 {
		return
	}
	if c.checkvisited(url) {
		return
	}
	body, urls, err := fetcher.Fetch(url)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Printf("found: %s %q\n", url, body)
	for _, u := range urls {
		c.wg.Add(1)
		go Crawl(u, depth-1, fetcher)
	}
	return
}

func main() {
	c.wg.Add(1)
	Crawl("http://golang.org/", 4, fetcher)
	c.wg.Wait()
	// Not ideal to sleep on the main thread.
	//time.Sleep(5*time.Second)
}

// fakeFetcher is Fetcher that returns canned results.
type fakeFetcher map[string]*fakeResult

type fakeResult struct {
	body string
	urls []string
}

func (f fakeFetcher) Fetch(url string) (string, []string, error) {
	if res, ok := f[url]; ok {
		return res.body, res.urls, nil
	}
	return "", nil, fmt.Errorf("not found: %s", url)
}

// fetcher is a populated fakeFetcher.
var fetcher = fakeFetcher{
	"http://golang.org/": &fakeResult{
		"The Go Programming Language",
		[]string{
			"http://golang.org/pkg/",
			"http://golang.org/cmd/",
		},
	},
	"http://golang.org/pkg/": &fakeResult{
		"Packages",
		[]string{
			"http://golang.org/",
			"http://golang.org/cmd/",
			"http://golang.org/pkg/fmt/",
			"http://golang.org/pkg/os/",
		},
	},
	"http://golang.org/pkg/fmt/": &fakeResult{
		"Package fmt",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
	"http://golang.org/pkg/os/": &fakeResult{
		"Package os",
		[]string{
			"http://golang.org/",
			"http://golang.org/pkg/",
		},
	},
}
