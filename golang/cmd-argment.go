package main

import (
	"flag"
	"fmt"
	"os"
)

var version = "1.0.0"
var ip *string
var port *int

func init() {
	var showVerison bool
	flag.BoolVar(&showVerison, "v", false, "show version")
	flag.BoolVar(&showVerison, "version", false, "show version")

	ip = flag.String("ip", "127.0.0.1", "Set ip address")
	port = flag.Int("port", 3000, "Set ip port")

	flag.Parse()
	if showVerison {
		fmt.Println("version:", version)
		os.Exit(0)
	}
}

func main() {
	fmt.Println("ip:", *ip, "port:", *port)
}
