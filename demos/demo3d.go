package demos


import (
	"fmt"
	"lourah.com/oops/demo/screen"
	"lourah.com/oops/demo/geometry"
	"lourah.com/oops/demo/registry"
	"math"
	"time"
	"runtime"
);

var   Entry *registry.Entry  = &registry.Entry{
	Name:"Demo3d",
	Summary:"A simple example showing how to use go language and interfaces",
	Handler:func () {
		runtime.MemProfileRate = 0;
		fmt.Printf("demo::Rendering::Begin\n");

		shape := geometry.NewShape();
		shape2 := geometry.NewShape();
		var t []*geometry.Pixel;
		xAxis := geometry.NewShape();
		yAxis := geometry.NewShape();
		zAxis := geometry.NewShape();
		ansi := screen.NewAnsi();
		red := screen.RGB([3]byte{255, 0, 0});
		green := screen.RGB([3]byte{0, 192, 0});
		blue := screen.RGB([3]byte{0, 127, 127});

		renderer := geometry.NewRenderer(160, 50, &geometry.APoint{30, 30, 100});

		for i:=0; i<360; i++ {
			angle := geometry.ToRadian(float64(i)/1);
			shape = geometry.Append(shape, &geometry.APoint{15*math.Cos(3*angle), 15*math.Sin(2*angle), 15*math.Sin(angle)}, red);
			shape2 = geometry.Append(shape2, &geometry.APoint{15*math.Cos(3*angle), 15*math.Sin(angle), 15*math.Sin(5*angle)}, blue);
		}

		for i:=-500; i<500; i++ {
			f := float64(i/10);
			xAxis = geometry.Append(xAxis, &geometry.APoint{f,0,0}, green);
			yAxis = geometry.Append(yAxis, &geometry.APoint{0,f,0}, green);
			zAxis = geometry.Append(zAxis, &geometry.APoint{0,0,f}, green);
		}


		defer func () { fmt.Println("Defered 1::", len(shape)); }();

		renderer.Render(xAxis);
		renderer.Render(yAxis);
		renderer.Render(zAxis);
		renderer.Render(shape);
		t = shape2;
		renderer.Render(t);
		for i:=0; i<360; i++ {
			f := float64(i);
			renderer.Draw(ansi);
			renderer.Render(
				renderer.Translate(
					renderer.Rotate(
						shape, geometry.ToRadian(f*.006), geometry.ToRadian(f*.001), geometry.ToRadian(f*.002)), &geometry.AVector{0, 0, float64(i)/720},
					));
					t = renderer.Rotate(shape2, geometry.ToRadian(3), geometry.ToRadian(5), geometry.ToRadian(4));
					t = renderer.Translate(t, &geometry.AVector{0, 0, -float64(i)/720});
					renderer.Render(t);
					renderer.Render(xAxis);
					renderer.Render(yAxis);
					renderer.Render(zAxis);
					if false { time.Sleep(100 * time.Millisecond); }
				}
				fmt.Printf("demo::End\n");
			}};
