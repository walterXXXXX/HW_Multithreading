#pragma once
#include<string>
#include<vector>
#include"shape.h"

class Sqr : public Shape {
public:
	Sqr(Coord coordA, Coord coordB, Coord coordC, Coord coordD);

	std::string getInfo() override;

protected:
	void calculates() override;
};

// методы масштабирования не отличаются от класса Shape
