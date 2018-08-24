package main

import "fmt"

type Writer interface {
	Write()
	SWrite(s string)
}

type A struct {
	name string
}

func (a A) Write() {
	fmt.Println("struct A :", a.name)
}

type B struct {
	name string
}

func (b B) Write() {
	fmt.Println("struct B :", b.name)
}

func (b B) SWrite(s string) {
	fmt.Println("struct B :", fmt.Sprint(s, b.name))
}

func my_print(w Writer) {
	// w.SWrite("decoration: ")
}

func main() {
	x := A{"yuu"}
	my_print(x)

	y := B{"yuu"}
	my_print(y)
}
