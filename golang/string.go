package main

import (
	"fmt"
	"strings"
)

func main() {
	hello := string("Hello, World!!")

	fmt.Println(hello)
	fmt.Println("HasPrefix(Hello) =", strings.HasPrefix(hello, "Hello"))
	fmt.Println("HasSuffix(World) =", strings.HasSuffix(hello, "World"))
	fmt.Println("Contains(!) =", strings.Contains(hello, "!"))
	for index, value := range strings.Fields(hello) {
		fmt.Println("Fields", index, value)
	}
	for index, value := range strings.Split(hello, ",") {
		fmt.Println("Split", index, value)
	}
	// We don't understand well enough yet for argument 4.
	fmt.Println("Replace(World)", strings.Replace(hello, "World", "世界", 1))
}
