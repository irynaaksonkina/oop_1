#pragma once

#include "Shape.h"

class Rectangle : public Shape {
private:
	int width;
	int height;

public:
	Rectangle(int id, int x, int y, char color, bool filled, int width, int height);

	void draw(std::vector<std::string>& grid) const override;
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
};