package main

import (
	"fmt"

	"github.com/deckarep/golang-set"
)

func main() {
	s1 := mapset.NewSet()
	s1.Add(1)
	s1.Add(2)
	s1.Add(3)

	s2 := mapset.NewSet()
	s2.Add(1)
	s2.Add(3)

	diff := s1.Difference(s2)
	fmt.Println(diff)
}
