#pragma once
#include<string>
#include<vector>
#include"shape.h"

class Line : public Shape {
public:
	Line(Coord coordA, Coord coordB);

protected:
	void calculates() override;
};

// методы масштабирования не отличаются от класса Shape
