package geometry

import "math"

type Vector struct {
	u,v,w float64
};


func (vector *Vector) Create(u,v,w float64) {
	vector.u = u;
	vector.v = v;
	vector.w = w;
}

func (vector *Vector) Length() float64 {
	return math.Sqrt(vector.ScalarProduct(vector));
}

func (vector *Vector) ScalarProduct(v *Vector) float64 {
	return vector.u*v.u + vector.v*v.v + vector.w*v.w;
}

func (u *Vector) VectorialProduct(v *Vector) *Vector {
	var pv Vector;
	pv.Create( u.v*v.w - u.w*v.v,
		u.w*v.u - u.u*v.w,
		u.u*v.v - u.v*v.u,
	);
	return &pv;
}
