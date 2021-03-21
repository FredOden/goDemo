#include "angles.h"
#include "renderer.h"
#include "ansi.h"
#include <iostream>
#include <cmath>

void demo3d() {
	std::cerr << "demo::Rendering::Begin" << std::endl;

	Lourah::geometry::Shape shape, shape2, xAxis, yAxis, zAxis,t, s;
	Lourah::screen::Ansi ansi;
	Lourah::screen::AColor red(255, 0, 0), green(0, 192, 0), blue(0, 127, 127);
	Lourah::geometry::APoint camera(30, 30, 100);
	Lourah::geometry::Renderer renderer(160, 50, camera);


	for (int i=0; i<360; i++) {
		double angle = Lourah::geometry::toRadian(i/1);
		shape += Lourah::geometry::Pixel(Lourah::geometry::APoint(15*std::cos(3*angle), 15*std::sin(2*angle), 15*std::sin(angle)), red);
		shape2 += Lourah::geometry::Pixel(Lourah::geometry::APoint(15*std::cos(3*angle), 15*std::sin(angle), 15*std::sin(5*angle)), blue);
	}

	for (int i=-500; i<500; i++) {
		double f = (double)i/10;
		xAxis += Lourah::geometry::Pixel(Lourah::geometry::APoint(f,0,0), green);
		yAxis += Lourah::geometry::Pixel(Lourah::geometry::APoint(0,f,0), green);
		zAxis += Lourah::geometry::Pixel(Lourah::geometry::APoint(0,0,f), green);
	}


	renderer.render(xAxis);
	renderer.render(yAxis);
	renderer.render(zAxis);
	renderer.render(shape);
	s = shape;
	t = shape2;
	renderer.render(t);
	for (int i=0; i<360; i++) {
		//std::cerr << i << "{" << std::endl;
		double f = (double)i;
		//std::cerr << i << " draw" << std::endl;
		renderer.draw(ansi);
		//std::cerr << i << " renderer(trnslate(rotate" << std::endl;
		s = renderer.rotate(s, Lourah::geometry::toRadian(f*.6), Lourah::geometry::toRadian(f*.001), Lourah::geometry::toRadian(f*.002));
		s = renderer.translate(s, Lourah::geometry::AVector(0, 0, f/720));
		//std::cerr << i << " renderer.rotate" << std::endl;
		t = renderer.rotate(shape2, Lourah::geometry::toRadian(3), Lourah::geometry::toRadian(5), Lourah::geometry::toRadian(4));
		//std::cerr << i << " renderer.translate" << std::endl;
		t = renderer.translate(t, Lourah::geometry::AVector(0, 0, -f/720));
		renderer.render(s);
		renderer.render(t);
		renderer.render(xAxis);
		renderer.render(yAxis);
		renderer.render(zAxis);
		//std::cerr << "}" << std::endl;
	}
	std::cerr << "demo::End" << std::endl;
};

int main(int argc, char **argv) {

	try {
		demo3d();
	} catch(std::exception& e) {
		std::cerr << "ERROR::" << e.what() << std::endl;
	}
}
