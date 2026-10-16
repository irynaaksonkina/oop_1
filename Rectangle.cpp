#include "Rectangle.h"
#include <fstream>

Rectangle::Rectangle(int id, int x, int y, char color, bool filled, int width, int height) 
	: Shape(id, x, y, color, filled), width(width), height(height) {

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

void Rectangle::getBounds(int& left, int& top, int& right, int& bottom) const {
	left = x;
	top = y;
	right = x + width - 1;
	bottom = y + height - 1;
}

std::string Rectangle::getType() const {
	return "rectangle";
}

std::string Rectangle::getParamsString() const {
	return std::to_string(width) + " " + std::to_string(height);
}

void Rectangle::saveToFile(std::ofstream& file) const {
	file << "rectangle " << (filled ? "fill" : "frame") << " "
		<< color << " " << x << " " << y << " "
		<< width << " " << height << "\n";
}

bool Rectangle::edit(const std::vector<std::string>& args) {
	if (args.size() != 2) return false;
	width = std::stoi(args[0]);
	height = std::stoi(args[1]);
	return true;
}