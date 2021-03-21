#ifndef LOURAH_GEOMETRY_APOINT_H
#define LOURAH_GEOMETRY_APOINT_H
#include "column.h"
#include "vectors.h"
namespace Lourah {
	namespace geometry {
		class APoint : public AColumn {
			public:
				static const int X = 0;
				static const int Y = 1;
				static const int Z = 2;
				double xyz[3] = {0, 0, 0};
				APoint() {}
				inline APoint(double x, double y, double z) { xyz[X] = x; xyz[Y] = y; xyz[Z] = z; }

				inline AVector to (APoint &p) { return AVector(p.xyz[X] - xyz[X], p.xyz[Y] - xyz[Y], p.xyz[Z] - xyz[Z]); }
				inline APoint translate (const AVector &v) { return APoint(xyz[X] + v.uvw[AVector::U], xyz[Y] + v.uvw[AVector::V], xyz[Z] + v.uvw[AVector::W]); }

				inline double& operator [] (int i) { return xyz[i]; }
				inline double at(int i) { return xyz[i]; }
				inline void feed(int i, double value) { xyz[i] = value; }
		};
	}
}
#endif
