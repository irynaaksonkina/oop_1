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

void handleAdd(Board& board, const std::vector<std::string>& args, int& nextId) {
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

    int x = 0;
    int y = 0;

    try {
        if (type == "rectangle" && args.size() == 5) {
            board.addShape(std::make_unique<Rectangle>(nextId, 0, 0, color, filled, std::stoi(args[3]), std::stoi(args[4])));
        }
        else if (type == "circle" && args.size() == 4) {
            board.addShape(std::make_unique<Circle>(nextId, 0, 0, color, filled, std::stoi(args[3])));
        }
        else if (type == "triangle" && args.size() == 5) {
            board.addShape(std::make_unique<Triangle>(nextId, 0, 0, color, filled, std::stoi(args[3]), std::stoi(args[4])));
        }
        else if (type == "line" && args.size() == 5) {
            board.addShape(std::make_unique<Line>(nextId, 0, 0, color, filled, std::stoi(args[3]), args[4][0]));
        }
        else {
            std::cout << "error: unknown shape type or wrong number of parameters\n";
            return;
        }
        std::cout << nextId << " " << type << " added\n";
        nextId++;
    }

    catch (...) {
        std::cout << "error: invalid number in arguments\n";
    }
}

int main() {
	Board board(80, 25);
    int nextId = 1;
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
            handleAdd(board, args, nextId);
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
                int id = std::stoi(args[0]);
                found = board.selectById(id);
            }
            else if (args.size() == 2) {
                int x = std::stoi(args[0]);
                int y = std::stoi(args[1]);
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
            int newX = std::stoi(args[0]);
            int newY = std::stoi(args[1]);

            if (board.moveSelected(newX, newY)) {
                std::cout << "shape moved\n";
            }
            else {
                std::cout << "error: no shape selected\n";
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
            else {
                if (board.load(args[0])) {
                    std::cout << "board loaded\n";
                }
                else {
                    std::cout << "error: could not load file\n";
                }
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

