#pragma once

#include "Shape.h"

class Triangle : public Shape {
private:
	int height;

public:
	Triangle(int id, int x, int y, char color, bool filled, int height);

	void draw(std::vector<std::string>& grid) const override;
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
	std::string getParamsString() const override;
};