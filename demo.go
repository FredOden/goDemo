package main


import (
	"fmt"
	"lourah.com/oops/demo/geometry"
	"math"
	"time"
);


func main() {
	fmt.Printf("demo::Rendering::Begin\n");

	shape := geometry.NewShape();
	shape2 := geometry.NewShape();
	var s,t []*geometry.Pixel;
	xAxis := geometry.NewShape();
	yAxis := geometry.NewShape();
	zAxis := geometry.NewShape();
	red := geometry.RGB([3]byte{255, 0, 0});
	green := geometry.RGB([3]byte{0, 192, 0});
	blue := geometry.RGB([3]byte{0, 127, 127});

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
	
	renderer.Render(xAxis);
	renderer.Render(yAxis);
	renderer.Render(zAxis);
	s = shape;
	renderer.Render(s);
	t = shape2;
	renderer.Render(t);
	for i:=0; i<360; i++ {
		renderer.Draw();
		s = renderer.Rotate(shape, geometry.ToRadian(6), geometry.ToRadian(1), geometry.ToRadian(2));
		s = renderer.Translate(s, &geometry.AVector{0, 0, float64(i)/720});
		renderer.Render(xAxis);
		renderer.Render(yAxis);
		renderer.Render(zAxis);
		renderer.Render(s);
		t = renderer.Rotate(shape2, geometry.ToRadian(3), geometry.ToRadian(5), geometry.ToRadian(4));
		t = renderer.Translate(t, &geometry.AVector{0, 0, -float64(i)/720});
		renderer.Render(t);
		if true { time.Sleep(100 * time.Millisecond); }
	}
	fmt.Printf("demo::End\n");
};
