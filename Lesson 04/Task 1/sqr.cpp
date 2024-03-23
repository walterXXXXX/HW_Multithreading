#define _USE_MATH_DEFINES
#include"sqr.h"
#include<cmath>

Sqr::Sqr(Coord coordA, Coord coordB, Coord coordC, Coord coordD) {
	name = "Прямоугольник";
	type = Type::SQR;
	// дополнительно можно добавить выбрасывание исключения при некорректном вводе координат
	coords.push_back(coordA);
	coords.push_back(coordB);
	coords.push_back(coordC);
	coords.push_back(coordD);
	calculates();
}

std::string Sqr::getInfo() {
	std::string result = Shape::getInfo() + "Площадь прямоугольника: " + std::to_string(square) + "\n";
	return result;
}

void Sqr::calculates() {
	int a = coords[2].x - coords[0].x;
	int b = coords[2].y - coords[0].y;
	square = a * b;
}