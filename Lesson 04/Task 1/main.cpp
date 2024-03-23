#include <iostream>
#include <memory>
#include "transform.h"
#include "shape.h"
#include "line.h"
#include "sqr.h"
#include "cube.h"
#include "circle.h"
#include "cylinder.h"

int main() {
	setlocale(LC_ALL, "");

	Shape shape;
	Line line({ 2,2,0 }, { 5,5,0 });
	Sqr sqr({0,0,0}, {0,2,0}, {3,2,0}, {3,0,0});
	Cube cube({ 0,0,0 }, { 0,2,0 }, { 3,2,0 }, { 3,0,0 },
			  { 0,0,5 }, { 0,2,5 }, { 3,2,5 }, { 3,0,5 });
	Circle circle({ 1,1,1 }, 10);
	Cylinder cylinder({ 3,3,3 }, 5, 15);

	std::vector<Shape*> shapes1;
	shapes1.push_back(&line);
	shapes1.push_back(&sqr);
	shapes1.push_back(&cube);
	shapes1.push_back(&circle);
	shapes1.push_back(&cylinder);

	std::cout << "Исходные фигуры:\n";
	for (const auto& shape : shapes1) {
		std::cout << shape->getInfo();
	}
	std::cout << "\n\n";

	std::cout << "Новые фигуры со смещением на (2, 2, 2):\n";
	std::vector<std::unique_ptr<Shape>> shapes2;
	for (const auto& shape : shapes1) {
		shapes2.push_back(std::move(transform(*shape).shift(2,2,2)));
	}
	for (const auto& shape : shapes2) {
		std::cout << shape->getInfo();
	}
	std::cout << "\n\n";

	std::cout << "Те же фигуры с уменьшением масштаба в 2 раза:\n";
	for (auto& shape : shapes2) {
		shape->scale(2);
		std::cout << shape->getInfo();
	}

	return 0;
}