#pragma once
#include<string>
#include<vector>
#include"shape.h"

class Circle : public Shape {
public: 
	Circle(Coord center, double radius);

	double getRadius();

	std::string getInfo() override;
	
	void scaleX(int a) override;
	
	void scaleY(int d) override;
	
	void scaleZ(int e) override;
	
	void scale(int s) override;

protected:
	double R = 0; // радиус
	
	void calculates() override;
};