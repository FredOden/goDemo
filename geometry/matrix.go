package geometry

import (
	"math"
	"reflect"
)

type AMatrix [9]float64;

func NewRot(angles [3]float64) *AMatrix {
	var c, s [3]float64;
	for i:= 0; i < 3; i++ {
		c[i],s[i] =  math.Cos(angles[i]) , math.Sin(angles[i]);
	}
	rot :=  &AMatrix {
		c[1]*c[2],                  -s[2]*c[1],                  s[1],
		s[0]*s[1]*c[2] + c[0]*s[2], -s[0]*s[1]*s[2] + c[0]*c[2], -s[0]*c[1],
		-c[0]*s[1]*c[2] + s[0]*s[2], c[0]*s[1]*s[2] + s[0]*c[2], c[0]*c[1],
	};
	return rot;
}

func (m *AMatrix) MatrixProduct (p *AMatrix) *AMatrix {
	r := &AMatrix {
		m[0]*p[0] + m[1]*p[3] + m[2]*p[6], m[0]*p[1] + m[1]*p[4] + m[2]*p[7], m[0]*p[2] + m[1]*p[5] + m[2]*p[8], 
		m[3]*p[0] + m[4]*p[3] + m[5]*p[6], m[3]*p[1] + m[4]*p[4] + m[5]*p[7], m[3]*p[2] + m[4]*p[5] + m[5]*p[8], 
		m[6]*p[0] + m[7]*p[3] + m[8]*p[6], m[6]*p[1] + m[7]*p[4] + m[8]*p[7], m[6]*p[2] + m[7]*p[5] + m[8]*p[8], 
	};
	return r;
}

// Transform will apply the m *AMatrix on a AColumn object
// for example there are implementations of AColumn interface on
// APoint and AVector type
// for example to apply on a *APoint object and getting resukting APoint:
// var pTo *APoint;
// pTo = mr.Transform(pFrom).(*APoint);
// seet .(*APoint) is a type assertion on AColumn
//
// Note that AColumn is substitued by *Type because implementing func (*Type) interfaceMember(...) ... { ... }
//
func (m *AMatrix) Transform(v AColumn) AColumn {
	columnPtr := reflect.New(reflect.TypeOf(v).Elem());
	k := columnPtr.Interface().(*APoint);
	av := [3]float64{v.at(0), v.at(1), v.at(2)};

	k.feed(0, m[0]*av[0] + m[1]*av[1] + m[2]*av[2]);;
	k.feed(1, m[3]*av[0] + m[4]*av[1] + m[5]*av[2]);;
	k.feed(2, m[6]*av[0] + m[7]*av[1] + m[8]*av[2]);;

	return k;
}
