package main

import (
	"fmt"
	"github.com/dustin/go-humanize"
	"os"
)

func main() {
	if len(os.Args) != 0 {
		os.Exit(1)
	}

	name := os.Args[1]
	s, _ := os.Stat(name)
	fmt.Printf("%s: %s\n", name, humanize.Bytes(uint64(s.Size())))
}
