package geometry

import "math"

const PI = math.Pi;
const Pi = math.Pi;
const TWOPI = 2.0 * math.Pi;
const invPI = 1.0 / math.Pi;
const FLAT = 180.0;
const invFLAT = 1.0 / FLAT;

func ToDegree(radian float64) float64 { return FLAT*radian*invPI; }
func ToRadian(degree float64) float64 { return PI*degree*invFLAT; }
