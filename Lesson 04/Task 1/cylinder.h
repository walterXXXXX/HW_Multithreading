#pragma once
#include<string>
#include<vector>
#include"shape.h"
#include"circle.h"

class Cylinder : public Circle {
public:
	Cylinder(Coord center, double radius, double height);
	
	double getHeight();
	
	std::string getInfo() override;
	
	void scaleX(int a) override;
	
	void scaleY(int d) override;
	
	void scaleZ(int e) override;
	
	void scale(int s) override;

protected: 
	double H = 0; // высота
	
	void calculates() override;
};