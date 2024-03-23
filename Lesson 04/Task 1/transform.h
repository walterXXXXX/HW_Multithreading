#pragma once
#include"shape.h"
#include <memory>

// Не совсем понял назначение этого класса, но решил его оставить
// Класс способен порождать фигуры, подобные той, на основе
// которой он был проинициализирован.
// Для обеспечения полиморфизма объекты заменены на указатели

class transform
{
public:
	transform(Shape& sh);
	std::unique_ptr<Shape> shift(int m, int n, int k);
	std::unique_ptr<Shape> scaleX(int a);
	std::unique_ptr<Shape> scaleY(int d);
	std::unique_ptr<Shape> scaleZ(int e);
	std::unique_ptr<Shape> scale(int s);

private:
	std::unique_ptr<Shape> shape;
	std::unique_ptr<Shape> getCopy(Shape& sh);
};

