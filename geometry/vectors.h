#ifndef LOURAH_GEOMETRY_AVECTOR_H
#define LOURAH_GEOMETRY_AVECTOR_H
#include "column.h"
#include "cmath"
namespace Lourah {
	namespace geometry {
		class AVector : public AColumn {
			public:
				static const int U = 0;
				static const int V = 1;
				static const int W = 2;
				double uvw[3] = {0, 0, 0};
				AVector() {};
				inline AVector(double u, double v, double w) {
					uvw[U] = u;
					uvw[V] = v;
					uvw[W] = w;
				}
				inline double length() {
					return std::sqrt((*this) * (*this));
				}
				inline double operator * (AVector& v) {
					return this->uvw[U]*v.uvw[U] + this->uvw[V]*v.uvw[V] + this->uvw[W]*v.uvw[W];
				}
				inline AVector operator % (AVector& v) {
					return AVector(this->uvw[V]*v.uvw[W] - this->uvw[W]*v.uvw[V], this->uvw[W]*v.uvw[U] - this->uvw[U]*v.uvw[W], this->uvw[U]*v.uvw[V] - this->uvw[V]*v.uvw[U]);
				}
				inline double& operator [] (int i) { return uvw[i]; }
				inline double at(int i) { return uvw[i]; }
				inline void feed(int i, double value) { uvw[i] = value; }
		};
	}
}
#endif
