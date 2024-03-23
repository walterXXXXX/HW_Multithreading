#pragma once
#include<string>
#include<vector>
#include"shape.h"

class Cube : public Shape {
public:
	Cube(Coord coord1_A, Coord coord1_B, Coord coord1_C, Coord coord1_D,
		 Coord coord2_A, Coord coord2_B, Coord coord2_C, Coord coord2_D);
	
	std::string getInfo() override;
	
	void scale(int s) override;

protected:
	void calculates() override;
};
