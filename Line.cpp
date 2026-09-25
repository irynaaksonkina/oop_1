#include "Line.h"
#include <cmath>
#include <fstream>

Line::Line(int id, int x, int y, char color, bool filled, int length, char direction)
	: Shape(id, x, y, color, filled), length(length), direction(direction) {

}


void Line::draw(std::vector<std::string>& grid) const {
	int boardHeight = static_cast<int>(grid.size());
	if (boardHeight == 0) {
		return;
	}
	int boardWidth = static_cast<int>(grid[0].size());

	for (int i = 0; i < length; i++) {
		int drawX;
		int drawY;

		if (direction == 'h') {
			drawX = x + i;
			drawY = y;
		}
		else {
			drawX = x;
			drawY = y + i;
		}


		if (drawX < 0 || drawX >= boardWidth || drawY < 0 || drawY >= boardHeight) {
			continue;
		}

		grid[drawY][drawX] = color;
	}
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