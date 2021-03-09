package main


import (
	"fmt"
	"lourah.com/oops/demo/geometry"
);


func main() {
	fmt.Printf("demo::Begin\n");
	var p,q,r *geometry.Point;
	var pv *geometry.Vector;
	p = new(geometry.Point);
	q = new(geometry.Point);
	r = new(geometry.Point);
	p.Create(1.0, 2.0, 3.0);
	q.Create(2.0, 2.0, 3.0);
	r.Create(3.0, 2.0, 4.0);
	p.SetX(15);
	fmt.Println("p::Println::", p);
	fmt.Printf("p:%f\n", p.GetX());
	fmt.Printf("p.To(q).Length():%f\n", p.To(q).Length());
	var i int;
	for i= 0; i < 1000000; i++ {
		pv = p.To(q).VectorialProduct(p.To(r));
	}
	fmt.Println("p.VectorialProduct::", i, "::",  pv);
	fmt.Printf("demo::End\n");
	};
