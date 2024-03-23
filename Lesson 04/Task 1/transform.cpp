#include "transform.h"
#include "shape.h"
#include "line.h"
#include "sqr.h"
#include "cube.h"
#include "circle.h"
#include "cylinder.h"
#include <memory>

transform::transform(Shape& sh)
{
	// создаем копию полученного объекта в зависимости от типа
	shape = getCopy(sh);
}

std::unique_ptr<Shape> transform::getCopy(Shape& sh) {
	switch (sh.getType()) {
	case Shape::Type::ABSTRACT:
		return std::make_unique<Shape>(sh);
		break;
	case Shape::Type::LINE:
		return std::make_unique<Line>(*(dynamic_cast<Line*>(&sh)));
		break;
	case Shape::Type::SQR:
		return std::make_unique<Sqr>(*(dynamic_cast<Sqr*>(&sh)));
		break;
	case Shape::Type::CUBE:
		return std::make_unique<Cube>(*(dynamic_cast<Cube*>(&sh)));
		break;
	case Shape::Type::CIRCLE:
		return std::make_unique<Circle>(*(dynamic_cast<Circle*>(&sh)));
		break;
	case Shape::Type::CYLINDER:
		return std::make_unique<Cylinder>(*(dynamic_cast<Cylinder*>(&sh)));
		break;
	}
}

std::unique_ptr<Shape> transform::shift(int m, int n, int k)
{
	shape->shift(m, n, k);
	return getCopy(*shape);
}

std::unique_ptr<Shape> transform::scaleX(int a)
{
	shape->scaleX(a);
	return getCopy(*shape);
}

std::unique_ptr<Shape> transform::scaleY(int d)
{
	shape->scaleY(d);
	return getCopy(*shape);
}

std::unique_ptr<Shape> transform::scaleZ(int e)
{
	shape->scaleZ(e);
	return getCopy(*shape);
}

std::unique_ptr<Shape> transform::scale(int s)
{
	shape->scale(s);
	return getCopy(*shape);
}
