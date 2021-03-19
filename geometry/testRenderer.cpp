#include "angles.h"
#include "renderer.h"
#include "ansi.h"
#include <iostream>

int main(int argc, char **argv) {

	Lourah::screen::Ansi ansi;

	std::cout << "testRenderer::Starting" << std::endl;
	Lourah::geometry::Shape s;
	for(int i = 0; i < 10; i++) {
		Lourah::geometry::APoint at(i, i+10, i);
		Lourah::screen::AColor color(255, 0, i);
		Lourah::geometry::Pixel pixel(at, color);
		s += pixel;
	}
	std::cout << "s,length::" << s.getLength() << std::endl;
	Lourah::geometry::APoint camera(10, 10, 200);
	Lourah::geometry::Renderer renderer(180, 50, camera);
	renderer.rotate(s, 0, 0, Lourah::geometry::toRadian(-90));
	for(int i = 0; i < s.getLength(); i++) {
		Lourah::geometry::Pixel p = s[i];
		std::cout 
			<< "Pixel::p3d(" << p.p3d[0] << ","  << p.p3d[1] << "," << p.p3d[2] << ")"
			<< "Pixel::color(" << p.color[0] << ","  << p.color[1] << "," << p.color[2] << ")"
			<< std::endl;

	}
	renderer.render(s);


	renderer.draw(ansi);

	
}
