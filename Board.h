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
	int selectedIndex = -1;

public:
	Board(int width, int height);

	void draw() const;

	void addShape(std::unique_ptr<Shape> shape);

	const std::vector<std::unique_ptr<Shape>>& getShapes() const;

	bool selectById(int id);
	bool selectByCoordinate(int x, int y);
	Shape* getSelectedShape() const;

	bool removeSelected();

	bool moveSelected(int newX, int newY);

	void clear();
	bool save(const std::string& filename) const;
	bool load(const std::string& filename);
	
	bool editSelected(const std::vector<std::string>& args);
};
