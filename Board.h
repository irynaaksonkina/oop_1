#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Shape.h"


class Board {
private:
	int width;
	int height;

	std::vector<std::unique_ptr<Shape>> shapes;

public:
	Board(int width, int height);

	void draw() const;

	void addShape(std::unique_ptr<Shape> shape);

};
