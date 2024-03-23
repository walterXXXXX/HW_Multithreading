#define _USE_MATH_DEFINES
#include"cylinder.h"
#include<cmath>

Cylinder::Cylinder(Coord center, double radius, double height) : Circle(center, radius){
	name = "Цилиндр";
	type = Type::CYLINDER;
	H = height;
	calculates();
}

double Cylinder::getHeight() { return H; }

std::string Cylinder::getInfo() {
	std::string result = Shape::getInfo() + "Площадь поверхности: " + std::to_string(square) + "\n" +
		"Объем: " + std::to_string(volume) + "\n";
	return result;
}

void Cylinder::calculates() {
	square = M_PI * R * R + 2 * R * H;
	volume = M_PI * R * R * H;
}

// методы масштабирования для цилиндра не определены в исходном файле, переопределим их пустыми методами
// для возможности доработки в дальнейшем
void Cylinder::scaleX(int a) {
}

void Cylinder::scaleY(int d) {
}

void Cylinder::scaleZ(int e) {
}

void Cylinder::scale(int s) {
}
