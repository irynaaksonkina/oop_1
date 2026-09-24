#include "Board.h"
#include <iostream>

Board::Board(int width, int height) : width(width), height(height) {

}

void Board::draw() const {
    for (int row = 0; row < height; row++) {
        std::string line(width, ' ');
        std::cout << line << "\n";
    }
}