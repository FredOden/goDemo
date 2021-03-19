#ifndef LOURAH_GEOMETRY_MATRIX_H
#define LOURAH_GEOMETRY_MATRIX_H
#include <cmath>
#include <cstring>
#include "points.h"
#include "vectors.h"
namespace Lourah {
	namespace geometry {


		class AMatrix {
			private:
				static const int __SIZE = 9*sizeof(double);
			public:
				double *m;
				AMatrix() {
					m = {new double[9]{0,0,0,0,0,0,0,0,0}};
				};
				AMatrix(double rx, double ry,  double rz) {
					double c[3], s[3];
					c[0] = std::cos(rx); s[0] = std::sin(rx);
					c[1] = std::cos(ry); s[1] = std::sin(ry);
					c[2] = std::cos(rz); s[2] = std::sin(rz);
					m = {new double[9] {
						c[1]*c[2],                  -s[2]*c[1],                  s[1],
						s[0]*s[1]*c[2] + c[0]*s[2], -s[0]*s[1]*s[2] + c[0]*c[2], -s[0]*c[1],
						-c[0]*s[1]*c[2] + s[0]*s[2], c[0]*s[1]*s[2] + s[0]*c[2], c[0]*c[1],
					}};
				}


				AMatrix operator * (AMatrix& p) {
					AMatrix r;
					free(r.m);
					r.m = {new double[9] {
						m[0]*p.m[0] + m[1]*p.m[3] + m[2]*p.m[6], m[0]*p.m[1] + m[1]*p.m[4] + m[2]*p.m[7], m[0]*p.m[2] + m[1]*p.m[5] + m[2]*p.m[8], 
						m[3]*p.m[0] + m[4]*p.m[3] + m[5]*p.m[6], m[3]*p.m[1] + m[4]*p.m[4] + m[5]*p.m[7], m[3]*p.m[2] + m[4]*p.m[5] + m[5]*p.m[8], 
						m[6]*p.m[0] + m[7]*p.m[3] + m[8]*p.m[6], m[6]*p.m[1] + m[7]*p.m[4] + m[8]*p.m[7], m[6]*p.m[2] + m[7]*p.m[5] + m[8]*p.m[8], 
					}};
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
				AVector operator * (AVector& v) {
					return AVector(
							m[0]*v.uvw[0] + m[1]*v.uvw[1] + m[2]*v.uvw[2],
							m[3]*v.uvw[0] + m[4]*v.uvw[1] + m[5]*v.uvw[2],
							m[6]*v.uvw[0] + m[7]*v.uvw[1] + m[8]*v.uvw[2]
						      );
				}

				APoint operator * (APoint& v) {
					return APoint(
							m[0]*v.xyz[0] + m[1]*v.xyz[1] + m[2]*v.xyz[2],
							m[3]*v.xyz[0] + m[4]*v.xyz[1] + m[5]*v.xyz[2],
							m[6]*v.xyz[0] + m[7]*v.xyz[1] + m[8]*v.xyz[2]
						     );
				}
		};	
	}
}
#endif
