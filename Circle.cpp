#include "Circle.h"
#include <cmath>

Circle::Circle(int id, int x, int y, char color, bool filled, int radius)
	: Shape(id, x, y, color, filled), radius(radius) {

}

void Circle::draw(std::vector<std::string>& grid) const {
	int boardHeight = static_cast<int>(grid.size());
	if (boardHeight == 0) {
		return;
	}
	int boardWidth = static_cast<int>(grid[0].size());

	for (int row = y - radius; row <= y + radius; row++) {
		for (int col = x - radius; col <= x + radius; col++) {
			int dx = col - x;
			int dy = row - y;
			double distance = std::sqrt(static_cast<double>(dx * dx + dy * dy));
			int roundedDistance = static_cast<int>(std::round(distance));

			bool isOnCircle = (roundedDistance == radius);

			if (!filled && !isOnCircle) {
				continue;
			}
			if (filled && roundedDistance > radius) {
				continue;
			}

			if (col < 0 || col >= boardWidth || row < 0 || row >= boardHeight) {
				continue;
			}

			grid[row][col] = color;

		}
	}
}

bool Circle::containsPoint(int px, int py) const {
	int dx = px - x;
	int dy = py - y;
	double distance = std::sqrt(static_cast<double>(dx * dx + dy * dy));
	int roundedDistance = static_cast<int>(std::round(distance));

	if (filled) {
		return roundedDistance <= radius;
	}

	return roundedDistance == radius;
}

bool Circle::fitsInBoard(int boardWidth, int boardHeight) const {
	int diameter = radius * 2 + 1;
	return diameter <= boardWidth && diameter <= boardHeight;
}

std::string Circle::getType() const {
	return "circle";
}

std::string Circle::getParamsString() const {
	return std::to_string(radius);
}