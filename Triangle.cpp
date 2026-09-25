#include "Triangle.h"
#include <cmath>

Triangle::Triangle(int id, int x, int y, char color, bool filled, int height)
	: Shape(id, x, y, color, filled), height(height) {

}

void Triangle::draw(std::vector<std::string>& grid) const {
	int boardHeight = static_cast<int>(grid.size());
	if (boardHeight == 0) {
		return;
	}

	int boardWidth = static_cast<int>(grid[0].size());	

	for (int row = 0; row < height; row++) {
		
		int halfWidth = row;

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

	double halfWidth = row;
	
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
	
	int maxHalfWidth = height - 1;
	int requiredWidth = maxHalfWidth * 2 + 1;


	return height <= boardHeight && requiredWidth <= boardWidth;

}

std::string Triangle::getType() const {
	return "triangle";
}

std::string Triangle::getParamsString() const {
	return std::to_string(height);
}

