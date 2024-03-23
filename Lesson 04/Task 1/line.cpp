#define _USE_MATH_DEFINES
#include"line.h"
#include<cmath>

Line::Line(Coord coordA, Coord coordB) {
	name = "Линия";
	type = Type::LINE;
	coords.push_back(coordA);
	coords.push_back(coordB);
}

void Line::calculates() { };