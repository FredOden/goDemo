#ifndef LOURAH_GEOMETRY_ACOLUMN_H
#define LOURAH_GEOMETRY_ACOLUMN_H
namespace Lourah {
	namespace  geometry {

		class AColumn {
			virtual double at(int) = 0; // should return the nth element of the column
			virtual void feed(int, double) = 0;
			virtual double& operator [] (int) = 0;
			//virtual AColumn newInstance() = 0;
			//getArray() [3]float64;
		};
	}
}
#endif
