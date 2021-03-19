package main


import (
	"fmt"
	"lourah.com/oops/demo/demos"
	"lourah.com/oops/demo/registry"
	"runtime/debug"
	"reflect"
	"strconv"
);

func main() {
	menu  := registry.NewRegister();

	menu.AddEntry(demos.Demo3d);;

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

	keys := reflect.ValueOf(menu).MapKeys();
	for {
		for i :=  0; i < len(keys); i++ {
			key := keys[i].String();
			fmt.Printf("%d - [%-10.10s%100.100s]\n", i + 1, key, menu[key].Summary);
		}
		var sChoice string;
		fmt.Print("Choice: ");
		fmt.Scanf("%s", &sChoice);
		if (sChoice == "q") { break; }
		if k, err := strconv.Atoi(sChoice); err == nil {
			k--;
			if k >=0 && k < len(keys) {
				menu[keys[k].String()].Handler();
			} else {
				continue;
			}
		}
	}
}
