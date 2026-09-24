#pragma once

#include <vector>
#include <string>

class Board {
private:
	int width;
	int height;

public:
	Board(int width, int height);

	void draw() const;

};
