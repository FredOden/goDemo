package geometry 

type AColor [4]byte;

const R = 0;
const G = 1;
const B = 2;
const A = 3;

func RGB(rgb [3]byte) *AColor { c := &AColor{rgb[0], rgb[1], rgb[2], 255}; return c; }
/*
func Gradiant(from *AColor, to *AColor, percentage float64)  *AColor {
}
*/
