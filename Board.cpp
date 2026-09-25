#include "Board.h"
#include <iostream>
#include <utility>
#include <fstream>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"

Board::Board(int width, int height) : width(width), height(height) {

}

void Board::draw() const {
    
    std::vector<std::string> grid(height, std::string(width, ' '));

    for (const auto& shape : shapes) {
        shape->draw(grid);
    }


    for (const std::string& line : grid) {
        std::cout << line << "\n";
    }
}

void Board::addShape(std::unique_ptr<Shape> shape) {
    shapes.push_back(std::move(shape));
}

const std::vector<std::unique_ptr<Shape>>& Board::getShapes() const {
    return shapes;
}

bool Board::selectById(int id) {
    for (size_t i = 0; i < shapes.size(); i++) {
        if (shapes[i]->getId() == id) {
            selectedIndex = static_cast<int>(i);
            return true;
        }
    }
    return false;
}

bool Board::selectByCoordinate(int x, int y) {
    for (int i = static_cast<int>(shapes.size()) - 1; i >= 0; i--) {
        if (shapes[i]->containsPoint(x, y)) {
            selectedIndex = i;
            return true;
        }
    }
    return false;
}

Shape* Board::getSelectedShape() const {
    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(shapes.size())) {
        return nullptr;
    }
    return shapes[selectedIndex].get();
}

bool Board::removeSelected() {
    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(shapes.size())) {
        return false;
    }

    shapes.erase(shapes.begin() + selectedIndex);
    selectedIndex = -1;
    return true;
}

bool Board::moveSelected(int newX, int newY) {
    if (selectedIndex == -1) {
        return false;
    }

    shapes[selectedIndex]->moveTo(newX, newY);

    std::unique_ptr<Shape> temp = std::move(shapes[selectedIndex]);
    shapes.erase(shapes.begin() + selectedIndex);
    shapes.push_back(std::move(temp));
    selectedIndex = static_cast<int>(shapes.size()) - 1;

    return true;
}

void Board::clear() {
    shapes.clear();
    selectedIndex = -1;
}

bool Board::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << width << " " << height << "\n";

    for (const auto& shape : shapes) {
        shape->saveToFile(file);
    }

    file.close();
    return true;
}

bool Board::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    int fWidth, fHeight;
    if (!(file >> fWidth >> fHeight)) return false;

    std::vector<std::unique_ptr<Shape>> tempShapes;

    std::string type, mode;
    char color;
    int x, y;
    int loadedId = 1;

    while (file >> type >> mode >> color >> x >> y) {
        bool filled = (mode == "fill");

        if (type == "rectangle") {
            int w, h;
            file >> w >> h;
            tempShapes.push_back(std::make_unique<Rectangle>(loadedId++, x, y, color, filled, w, h));
        }
        else if (type == "circle") {
            int r;
            file >> r;
            tempShapes.push_back(std::make_unique<Circle>(loadedId++, x, y, color, filled, r));
        }
        else if (type == "triangle") {
            int h, angle;
            file >> h >> angle;
            tempShapes.push_back(std::make_unique<Triangle>(loadedId++, x, y, color, filled, h, angle)); // 7 аргументів
        }
        else if (type == "line") {
            int len;
            char dir;
            file >> len >> dir;
            tempShapes.push_back(std::make_unique<Line>(loadedId++, x, y, color, filled, len, dir));
        }
    }

    file.close();

    width = fWidth;
    height = fHeight;
    shapes = std::move(tempShapes);
    selectedIndex = -1;
    return true;
}

bool Board::editSelected(const std::vector<std::string>& args) {
    if (selectedIndex < 0 || selectedIndex >= static_cast<int>(shapes.size())) {
        return false;
    }
    return shapes[selectedIndex]->edit(args);
}