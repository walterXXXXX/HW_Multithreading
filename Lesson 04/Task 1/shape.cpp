#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

Shape::Type Shape::getType() { return type; }

double Shape::getVolume() { return volume; }

double Shape::getSquare() { return square; }

std::vector<Shape::Coord> Shape::getCoords() { return coords; }

std::string Shape::getInfo() { 
	std::string result = "\n" + name + "\n" + "Координаты: ";
	for (Coord coord : coords)
		result += ("(" + std::to_string(coord.x) + ", " + std::to_string(coord.y) + ", " + std::to_string(coord.z) + "); ");
	result += "\n";
	return result; 
}

void Shape::shift(int m, int n, int k) {
	for (Coord& coord : coords) {
		coord.x += m;
		coord.y += n;
		coord.z += k;
	}
}

void Shape::scaleX(int a) {
	for (Coord& coord : coords)
		coord.x *= a;
	calculates();
}

void Shape::scaleY(int d) {
	for (Coord& coord : coords)
		coord.y *= d;
	calculates();
}

void Shape::scaleZ(int e) {
	for (Coord& coord : coords)
		coord.y *= e;
	calculates();
}

void Shape::scale(int s) {
	for (Coord& coord : coords) {
		coord.x /= s;
		coord.y /= s;
	}	
	calculates();
}

void Shape::calculates() { };