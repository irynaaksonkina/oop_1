#pragma once

#include "Shape.h"

class Rectangle : public Shape {
private:
	int width;
	int height;

public:
	Rectangle(int id, int x, int y, char color, bool filled, int width, int height);

	
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
	std::string getParamsString() const override;
	void saveToFile(std::ofstream& file) const override;
	bool edit(const std::vector<std::string>& args) override;
	void getBounds(int& left, int& top, int& right, int& bottom) const override;
};