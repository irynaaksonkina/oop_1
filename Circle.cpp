#include "Circle.h"
#include <cmath>
#include <fstream>

Circle::Circle(int id, int x, int y, char color, bool filled, int radius)
	: Shape(id, x, y, color, filled), radius(radius) {

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

void Circle::getBounds(int& left, int& top, int& right, int& bottom) const {
	left = x - radius;
	top = y - radius;
	right = x + radius;
	bottom = y + radius;
}

std::string Circle::getType() const {
	return "circle";
}

std::string Circle::getParamsString() const {
	return std::to_string(radius);
}

void Circle::saveToFile(std::ofstream& file) const {
	file << "circle " << (filled ? "fill" : "frame") << " "
		<< color << " " << x << " " << y << " "
		<< radius << "\n";
}

bool Circle::edit(const std::vector<std::string>& args) {
	if (args.size() != 1) return false;
	int newR = std::stoi(args[0]);
	if (newR <= 0) return false;

	radius = newR;
	return true;
}