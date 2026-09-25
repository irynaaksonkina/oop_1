#pragma once

#include "Shape.h"

class Line : public Shape {
private:
	int length;
	char direction;
public:
	Line(int id, int x, int y, char color, bool filled, int length, char direction);

	void draw(std::vector<std::string>& grid) const override;
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
	std::string getParamsString() const override;
	void saveToFile(std::ofstream& file) const override;
	bool edit(const std::vector<std::string>& args) override;
};