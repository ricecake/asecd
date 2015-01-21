package main;

import (
	"fmt"
	"github.com/ricecake/asecd/script"
)

func main() {
	script := script.NewJSEngine();

	fmt.Printf("%p\n", script)
}
