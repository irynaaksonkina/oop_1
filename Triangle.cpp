#include "Triangle.h"
#include <cmath>

Triangle::Triangle(int id, int x, int y, char color, bool filled, int height, int angle)
	: Shape(id, x, y, color, filled), height(height), angle(angle) {

}

void Triangle::draw(std::vector<std::string>& grid) const {
	int boardHeight = static_cast<int>(grid.size());
	if (boardHeight == 0) {
		return;
	}

	int boardWidth = static_cast<int>(grid[0].size());
	double angleInRadians = angle * 3.14159265 / 180.0;

	for (int row = 0; row < height; row++) {
		
		double halfWidthDouble = row * std::tan(angleInRadians);
		int halfWidth = static_cast<int>(std::round(halfWidthDouble));

		for (int col = -halfWidth; col <= halfWidth; col++) {
			int drawX = x + col;
			int drawY = y + row;

			if (drawX < 0 || drawX >= boardWidth || drawY < 0 || drawY >= boardHeight) {
				continue;
			}

			bool isEdge = (col == -halfWidth || col == halfWidth || row == height - 1);

			if (filled || isEdge) {
				grid[drawY][drawX] = color;
			}
		}

	}
}

bool Triangle::containsPoint(int px, int py) const {
	int row = py - y;

	if (row < 0 || row > height - 1) {
		return false;
	}

	double angleInRadians = angle * 3.14159265 / 180.0;
	double halfWidthDouble = row * std::tan(angleInRadians);
	int halfWidth = static_cast<int>(std::round(halfWidthDouble));
	
	int col = px - x;
	if (col < -halfWidth || col > halfWidth) {
		return false;
	}
	if (filled) {
		return true;
	}
	bool isEdge = (col == -halfWidth || col == halfWidth || row == height - 1);
	return isEdge;

}

bool Triangle::fitsInBoard(int boardWidth, int boardHeight) const {
	
	double angleInRadians = angle * 3.14159265 / 180.0;
	double halfWidthDouble = (height - 1) * std::tan(angleInRadians);
	int halfWidth = static_cast<int>(std::round(halfWidthDouble));

	int requiredWidth = halfWidth * 2 + 1;

	return height <= boardHeight && requiredWidth <= boardWidth;

}

std::string Triangle::getType() const {
	return "triangle";
}

std::string Triangle::getParamsString() const {
	return std::to_string(height) + " " + std::to_string(angle);
}

