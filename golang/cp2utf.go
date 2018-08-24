package main

import (
	"fmt"
	"golang.org/x/text/encoding/japanese"
	"log"
	"os/exec"
)

// CP932 to UTF-8 on windows
func main() {
	log.Print("START")
	cmd := exec.Command("dir")
	b, err := cmd.CombinedOutput()
	if err != nil {
		log.Fatal(err)
	}

	b, err = japanese.ShiftJIS.NewDecoder().Bytes(b)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(string(b))
}
