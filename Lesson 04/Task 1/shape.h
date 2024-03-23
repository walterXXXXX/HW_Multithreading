#pragma once
#include<string>
#include<vector>

class Shape
{
public:
	struct Coord {
		int x;
		int y; 
		int z;
	};

	enum Type {
		ABSTRACT,
		LINE,
		SQR,
		CUBE,
		CIRCLE,
		CYLINDER
	};

	Shape() = default;

	// конструктор и оператор копирования создаются по умолчанию
	
	Shape::Type getType();
	double getVolume();
	double getSquare();
	virtual std::vector<Coord> getCoords();
	virtual std::string getInfo();

	void shift(int m, int n, int k);
	virtual void scaleX(int a);
	virtual void scaleY(int d);
	virtual void scaleZ(int e);
	virtual void scale(int s);

protected:
	std::string name = "Абстрактная фигура";
	Type type = Type::ABSTRACT;
	std::vector<Coord> coords;
	virtual void calculates(); // метод обновляет расчетные данные фигуры при создании или трансформации
	double volume = 0;
	double square = 0;
};
