package main


import (
	"fmt"
	"lourah.com/oops/demo/geometry"
);


func main() {
	fmt.Printf("demo::APoint::AVector::Begin\n");
	var pv *geometry.AVector;
	p := &geometry.APoint{1,2,3};
	q := &geometry.APoint{2,2,3};
	r := &geometry.APoint{3,20,40};
	p[0] = 15;
	u := p.To(q);
	v := p.To(r);
	fmt.Println("p::Println::", p);
	fmt.Printf("p.To(q).Length():%f\n", u.Length());
	var i int;
	for i= 0; i < 1000000; i++ {
		pv = u.VectorialProduct(v);
	}
	fmt.Println("p.VectorialProduct::", i, "::",  pv);
	fmt.Printf("demo::End\n");
	};
