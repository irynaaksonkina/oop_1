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