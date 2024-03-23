#define _USE_MATH_DEFINES
#include"circle.h"
#include<cmath>

Circle::Circle(Coord center, double radius) {
	name = "Окружность";
	type = Type::CIRCLE;
	coords.push_back(center);
	R = radius;
	calculates();
}

double Circle::getRadius() { return R; }

std::string Circle::getInfo() {
	std::string result = Shape::getInfo() + "Радиус: " + std::to_string(R) + "\n" +
		"Площадь: " + std::to_string(square) + "\n";
	return result;
}

void Circle::calculates() {
	square = M_PI * R * R;
}

// методы масштабирования для окружности не определены в исходном файле, переопределим их пустыми методами
// для возможности доработки в дальнейшем
void Circle::scaleX(int a) {
}

void Circle::scaleY(int d) {
}

void Circle::scaleZ(int e) {
}

void Circle::scale(int s) {
}