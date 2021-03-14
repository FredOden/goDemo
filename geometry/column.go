package geometry

type AColumn interface {
	at(int) float64 // should return the nth element of the column
	feed(int, float64)
	//getArray() [3]float64;
}
