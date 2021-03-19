#ifndef lourah_geometry_angles
#define lourah_geometry_angles
#include "cmath"

namespace Lourah {
	namespace geometry {
		static const double PI = 3.141592653589793238462643383279502884;
		static const double TWOPI = 2.0 * PI;
		static const double INVPI = 1.0 / PI;
		static const double FLAT = 180.0;
		static const double INVFLAT = 1.0 / FLAT;

		inline double todegree(double radian) { return Lourah::geometry::FLAT*radian*Lourah::geometry::INVPI; }
		inline double toRadian(double degree) { return Lourah::geometry::PI*degree*Lourah::geometry::INVFLAT; }
	}
}
#endif
