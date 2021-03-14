package main


import (
	"fmt"
	"lourah.com/oops/demo/demos"
	"lourah.com/oops/demo/registry"
	"runtime/debug"
);

func main() {
	menu  := registry.NewRegister();

	menu.AddEntry(demos.Entry);;

	fmt.Println("Demo.go::Start");
	// Look at here, example of defer and recover feature
	// for error handling demonstration
	defer func () {
		if r:= recover(); r != nil {
			fmt.Println("Bad register entry ::", r);
			debug.PrintStack();
			// then exits normally from the enclosing function
		}
	}()
	fmt.Println(menu["Demo3d"].Summary);
	menu["Demo3d"].Handler();
	fmt.Println("Demo.go::End");
}
