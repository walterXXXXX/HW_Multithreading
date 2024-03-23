#define _USE_MATH_DEFINES
#include"cube.h"
#include<cmath>

Cube::Cube(Coord coord1_A, Coord coord1_B, Coord coord1_C, Coord coord1_D, // координаты основания 1
		   Coord coord2_A, Coord coord2_B, Coord coord2_C, Coord coord2_D  // координаты основания 2
) {
	name = "Параллелепипед";
	type = Type::CUBE;
	coords.push_back(coord1_A);
	coords.push_back(coord1_B);
	coords.push_back(coord1_C);
	coords.push_back(coord1_D);
	coords.push_back(coord2_A);
	coords.push_back(coord2_B);
	coords.push_back(coord2_C);
	coords.push_back(coord2_D);

	calculates();
}

std::string Cube::getInfo() {
	std::string result = Shape::getInfo() + "Площадь поверхности: " + std::to_string(square) + "\n" + 
		"Объем: " + std::to_string(volume) + "\n";
	return result;
}

void Cube::calculates() {
	int a = coords[6].x - coords[0].x;
	int b = coords[6].y - coords[0].y;
	int c = coords[6].z - coords[0].z;

	square = 2 * a * b + 2 * b * c + 2 * c * a;
	volume = a * b * c;
}

void Cube::scale(int s) {
	for (Coord& coord : coords) {
		coord.x /= s;
		coord.y /= s;
		coord.z /= s;
	}
	calculates();
}