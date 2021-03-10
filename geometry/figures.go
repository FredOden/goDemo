package geometry


type APoint [3]float64;
const X = 0;
const Y = 1;
const Z = 2;

func (from *APoint) To(to *APoint) *AVector { v := AVector{to[X] - from[X], to[Y] - from[Y], to[Z] - from[Z]}; return &v; };

func (p *APoint) Translate(v *AVector) *APoint { t := APoint{p[X] + v[U], p[Y] + v[V], p[Z] +v[W]}; return &t; }
