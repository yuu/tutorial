package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"os"
	"strings"
)

var buffering bool

func init() {
	flag.BoolVar(&buffering, "buffering", false, "use buffering io")
	flag.Parse()
}

func main() {
	var output io.Writer
	output = os.Stdout
	if buffering {
		output = bufio.NewWriter(os.Stdout)
	}

	for i := 0; i < 100; i++ {
		fmt.Fprintln(output, strings.Repeat("x", 100))
	}
}
