#include "Triangle.h"
#include <cmath>
#include <fstream>

Triangle::Triangle(int id, int x, int y, char color, bool filled, int height, int angle)
	: Shape(id, x, y, color, filled), height(height), angle(angle) {

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

void Triangle::getBounds(int& left, int& top, int& right, int& bottom) const {
	double angleInRadians = angle * 3.14159265 / 180.0;
	double halfWidthDouble = (height - 1) * std::tan(angleInRadians);
	int halfWidth = static_cast<int>(std::round(halfWidthDouble));

	left = x - halfWidth;
	top = y;
	right = x + halfWidth;
	bottom = y + height - 1;
}

std::string Triangle::getType() const {
	return "triangle";
}

std::string Triangle::getParamsString() const {
	return std::to_string(height) + " " + std::to_string(angle);
}

void Triangle::saveToFile(std::ofstream& file) const {
	file << "triangle " << (filled ? "fill" : "frame") << " "
		<< color << " " << x << " " << y << " "
		<< height << " " << angle << "\n"; 
}


bool Triangle::edit(const std::vector<std::string>& args) {
	if (args.size() != 2) return false;

	int newH = std::stoi(args[0]);
	int newAngle = std::stoi(args[1]);

	if (newH <= 0 || newAngle <= 0 || newAngle >= 90) return false;

	height = newH;
	angle = newAngle;
	return true;
}
