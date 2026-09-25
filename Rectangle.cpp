#include "Rectangle.h"

Rectangle::Rectangle(int id, int x, int y, char color, bool filled, int width, int height) 
	: Shape(id, x, y, color, filled), width(width), height(height) {

}

void Rectangle::draw(std::vector<std::string>& grid) const {
	int boardHeight = static_cast<int>(grid.size());
	if (boardHeight == 0) {
		return;
	}
	int boardWidth = static_cast<int>(grid[0].size());

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int drawX = x + col;
			int drawY = y + row;

			if (drawX < 0 || drawX >= boardWidth || drawY < 0 || drawY >= boardHeight) {
				continue;
			}

			bool isBorder = (row == 0 || row == height - 1 || col == 0 || col == width - 1);

			if (filled || isBorder) {
				grid[drawY][drawX] = color;
			}
		}
	}
}

bool Rectangle::containsPoint(int px, int py) const {
	bool insideBounds = (px >= x && px < x + width && py >= y && py < y + height);
	if (!insideBounds) {
		return false;
	}

	if (filled) {
		return true;
	}

	int localX = px - x;
	int localY = py - y;
	bool isBorder = (localX == 0 || localX == width - 1 || localY == 0 || localY == height - 1);
	return isBorder;
}

bool Rectangle::fitsInBoard(int boardWidth, int boardHeight) const {
	return width <= boardWidth && height <= boardHeight;
}

std::string Rectangle::getType() const {
	return "rectangle";
}

std::string Rectangle::getParamsString() const {
	return std::to_string(width) + " " + std::to_string(height);
}