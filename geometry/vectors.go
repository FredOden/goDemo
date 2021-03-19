package geometry

import "math"

type AVector [3]float64;

const U = 0;
const V = 1;
const W = 2;

func (vector *AVector) Length() float64 {
	return math.Sqrt(vector.ScalarProduct(vector));
}

func (u *AVector) ScalarProduct(v *AVector) float64 {
	return u[U]*v[U] + u[V]*v[V] + u[W]*v[W];
}

func (u *AVector) VectorialProduct(v *AVector) *AVector {
	pv := AVector{  u[V]*v[W] - u[W]*v[V], u[W]*v[U] - u[U]*v[W], u[U]*v[V] - u[V]*v[U] };
	return &pv;
}

func (p *AVector) at(i int) float64{ return p[i]; }
func (p *AVector) feed(i int, val float64) { p[i] = val; }
