#include "angles.h"
#include "matrix.h"
#include <iostream>
#include <iomanip> // std::setprecision here

int main(int argc, char **argv) {
	double angle = Lourah::geometry::toRadian(180);
	Lourah::geometry::AMatrix zM;
	Lourah::geometry::AMatrix zR(0, 0, angle);
	Lourah::geometry::APoint from(-1, 0, 30), to(1, 0, 30);
	Lourah::geometry::AVector v = from.to(to);

	std::cout << std::setprecision(20) << "PI::" << Lourah::geometry::PI << std::endl;
	std::cout << std::setprecision(20) << "toRadian::" << angle << std::endl;
	for(int i = 0; i < 9; i++) {
		std::cout << "zM[" << i << "]::" << zM.m[i] << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < 9; i++) {
		std::cout << "zR[" << i << "]::" << zR.m[i] << " ";
	}
	std::cout << std::endl;
	for(int i = 0; i < 3; i++) {
		std::cout << "v[" << i << "]::" << v.uvw[i] << " ";
	}
	std::cout << std::endl;
	Lourah::geometry::AVector rV = zR * v;
	for(int i = 0; i < 3; i++) {
		std::cout << "rV[" << i << "]::" << rV.uvw[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "v.length::" << v.length() << std::endl;
	std::cout << "rV.length::" << rV.length() << std::endl;
}
