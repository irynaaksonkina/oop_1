#include "Board.h"
#include <iostream>
#include <utility>

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