#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "Board.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"



std::vector<std::string> splitIntoWords(const std::string& line) {
    std::vector<std::string> words;
    std::istringstream stream(line);
    std::string word;

    while (stream >> word) {
        words.push_back(word);
    }

    return words;
}

bool parseInt(const std::string& text, int& result) {
    try {
        size_t pos = 0;
        int value = std::stoi(text, &pos);
        if (pos != text.size()) 
        {
            return false;
        }
        result = value;
        return true;
    }

    catch (const std::exception&) {
        return false;
    }
}


int nextId1(const Board& board) {
    int maxId = 0;
    for (const auto& shape : board.getShapes()) {
        if (shape->getId() > maxId) {
            maxId = shape->getId();
        }
    }
    return maxId + 1;
}

void handleAdd(Board& board, const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "error: not enough arguments for add\n";
        return;
    }

    if (args[0] != "fill" && args[0] != "frame") {
        std::cout << "error: fill mode must be 'fill' or 'frame'\n";
        return;
    }
    bool filled = (args[0] == "fill");

    char color = args[1][0];
    std::string type = args[2];

    int id = nextId1(board);
    

    try {
        std::unique_ptr<Shape> shape;
        if (type == "rectangle" && args.size() == 5) {
            shape = std::make_unique<Rectangle>(id, 0, 0, color, filled, std::stoi(args[3]), std::stoi(args[4]));
        }
        else if (type == "circle" && args.size() == 4) {
            shape = std::make_unique<Circle>(id, 0, 0, color, filled, std::stoi(args[3]));
        }
        else if (type == "triangle" && args.size() == 5) {
            shape = std::make_unique<Triangle>(id, 0, 0, color, filled, std::stoi(args[3]), std::stoi(args[4]));
        }
        else if (type == "line" && args.size() == 5) {
            shape = std::make_unique<Line>(id, 0, 0, color, filled, std::stoi(args[3]), args[4][0]);
        }
        else {
            std::cout << "error: unknown shape type or wrong number of parameters\n";
            return;
        }
        if (!board.addShape(std::move(shape))) {
            std::cout << "error: shape does not fit in the board\n";
            return;
        }
        std::cout << id << " " << type << " added\n";
    }

    catch (...) {
        std::cout << "error: invalid number in arguments\n";
    }
}

int main() {
	Board board(80, 25);

    board.addShape(std::make_unique<Rectangle>(1, 5, 3, 'r', false, 10, 5)); //тимчасово для перевірки
    board.addShape(std::make_unique<Circle>(2, 50, 12, 'a', true, 5));
    board.addShape(std::make_unique<Triangle>(3, 30, 2, 'g', false, 8, 30));
    board.addShape(std::make_unique<Line>(4, 5, 20, 'y', true, 20, 'v'));



	std::string line;
    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, line)) {
            break;
        }
        std::vector<std::string> words = splitIntoWords(line);
        if (words.empty()) {
            continue;
        }


        std::string command = words[0];
        std::vector<std::string> args(words.begin() + 1, words.end());




        if (command == "draw") {
            board.draw();
        }
        else if (command == "add") {
            handleAdd(board, args);
        }
        else if (command == "list") {
            for (const auto& shape : board.getShapes()) {
                std::cout << shape->getId()
                    << " " << shape->getType()
                    << " " << shape->getColor()
                    << " " << shape->getParamsString() << "\n";
            }
        }
        else if (command == "shapes") {
            std::cout << "circle radius\n";
            std::cout << "rectangle width height\n";
            std::cout << "triangle height angle\n";
            std::cout << "line length direction\n";
        }

        else if (command == "select") {
            bool found = false;


            if (args.size() == 1) {
                int id;
                if (!parseInt(args[0], id)) {
                    std::cout << "error: id must be a number\n";
                    continue;
                }
                found = board.selectById(id);
            }
            else if (args.size() == 2) {
                int x, y;
                if (!parseInt(args[0], x) || !parseInt(args[1], y)) {
                    std::cout << "error: coordinates must be numbers\n";
                    continue;
                }
                found = board.selectByCoordinate(x, y);
            }
            else {
                std::cout << "error: select needs id or x y\n";
            }

            if (found) {
                Shape* s = board.getSelectedShape();
                std::cout << s->getType();
                std::cout << " ";
                std::cout << s->getParamsString();
                std::cout << "\n";
            }
            else if (args.size() == 1 || args.size() == 2) {
                std::cout << "shape was not found\n";
            }
        }
        else if (command == "remove") {
            if (board.removeSelected()) {
                std::cout << "shape removed\n";
            }
            else {
                std::cout << "error: no shape selected\n";
            }
        }

        else if (command == "paint") {
            Shape* s = board.getSelectedShape();
            if (s == nullptr) {
                std::cout << "error: no shape selected\n";
            }
            else if (args.size() != 1) {
                std::cout << "error: paint needs a color\n";
            }
            else {
                char newColor = args[0][0];
                s->paint(newColor);
                std::cout << "shape painted\n";
            }
        }

        else if (command == "move") {
            int newX, newY;
            if (args.size() != 2 || !parseInt(args[0], newX) || !parseInt(args[1], newY)) {
                std::cout << "error: move needs two numbers: x y\n";
            } 
            else if (board.getSelectedShape() == nullptr) {
                std::cout << "error: no shape selected\n";
            }
            else if (board.moveSelected(newX, newY)) {
                std::cout << "shape moved\n";
            }
            else {
                std::cout << "error: new position is outside the board\n";
            }
        }

        else if (command == "clear") {
            board.clear();
            std::cout << "board cleared\n";
        }
        else if (command == "save") {
            if (args.empty()) {
                std::cout << "error: save needs a filename\n";
            }
            else {
                if (board.save(args[0])) {
                    std::cout << "board saved\n";
                }
                else {
                    std::cout << "error: could not save file\n";
                }
            }
        }
        else if (command == "load") {
            if (args.empty()) {
                std::cout << "error: load needs a filename\n";
            }
            else if (board.load(args[0])) {
                std::cout << "board loaded\n";
            }
            else {
                std::cout << "error: could not load file\n";
            }
 
       }

        else if (command == "edit") {
            if (!board.getSelectedShape()) {
                std::cout << "error: select shape\n";
            }
            else if (board.editSelected(args)) {
                std::cout << "shape edited\n";
            }
            else {
                std::cout << "error: wrong parameters\n";
            }
            }

		else if (command == "exit") {
			break;
		}
		else {
			std::cout << "unknown command\n";
		}

	}

	return 0;
}

