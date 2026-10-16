#pragma once

#include "Shape.h"

class Circle : public Shape {
private:
	int radius;
public:
	Circle(int id, int x, int y, char color, bool filled, int radius);

	
	bool containsPoint(int px, int py) const override;
	bool fitsInBoard(int boardWidth, int boardHeight) const override;
	std::string getType() const override;
	std::string getParamsString() const override;
	void saveToFile(std::ofstream& file) const override;
	bool edit(const std::vector<std::string>& args) override;
	void getBounds(int& left, int& top, int& right, int& bottom) const override;

};