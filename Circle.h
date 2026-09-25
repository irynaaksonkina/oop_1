#pragma once

#include "Shape.h"

class Circle : public Shape {
private:
	int radius;
public:
	Circle(int id, int x, int y, char color, bool filled, int radius);

	void draw(std::vector<std::string>& grid) const override;
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
	std::string getParamsString() const override;
	void saveToFile(std::ofstream& file) const override;
	bool edit(const std::vector<std::string>& args) override;
};