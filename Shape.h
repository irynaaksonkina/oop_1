#pragma once 

#include <vector>
#include <string>

class Shape {
protected:
	int id;
	int x, y;
	char color;
	bool filled;

public:
	Shape(int id, int x, int y, char color, bool filled);

	virtual ~Shape() = default;
	virtual void draw(std::vector<std::string>& grid) const = 0;
	virtual bool containsPoint(int px, int py) const = 0;
	virtual bool fitsInBoard(int boardWidth, int boardHeight) const = 0;
	virtual std::string getType() const = 0;
	virtual std::string getParamsString() const = 0;


	int getId() const;
	int getX() const;
	int getY() const;
	char getColor() const;
	bool isFilled() const;

	void paint(char newColor);
	void moveTo(int newX, int newY);

}; 