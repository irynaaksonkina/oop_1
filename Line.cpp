#include "Line.h"
#include <cmath>
#include <fstream>

Line::Line(int id, int x, int y, char color, bool filled, int length, char direction)
	: Shape(id, x, y, color, filled), length(length), direction(direction) {

}



bool Line::containsPoint(int px, int py) const {
	if (direction == 'h') {
		return py == y && px >= x && px < x + length;
	}
	else {
		return px == x && py >= y && py < y + length;
	}
}

bool Line::fitsInBoard(int boardWidth, int boardHeight) const {
	if (direction == 'h') {
		return length <= boardWidth;
	}
	else {
		return length <= boardHeight;
	}
}

void Line::getBounds(int& left, int& top, int& right, int& bottom) const {
	left = x;
	top = y;
	if (direction == 'h') {
		right = x + length - 1;
		bottom = y;
	}
	else {
		right = x;
		bottom = y + length - 1;
	}
}

std::string Line::getType() const {
	return "line";
}

std::string Line::getParamsString() const {
	return std::to_string(length) + " " + std::string(1, direction);
}

void Line::saveToFile(std::ofstream& file) const {
	file << "line " << (filled ? "fill" : "frame") << " "
		<< color << " " << x << " " << y << " "
		<< length << " " << direction << "\n";
}

bool Line::edit(const std::vector<std::string>& args) {
	if (args.size() != 2) return false;

	int newLen = std::stoi(args[0]);
	char newDir = args[1][0];

	if (newLen <= 0 || (newDir != 'h' && newDir != 'v')) {
		return false;
	}

	length = newLen;
	direction = newDir;
	return true;
}