#include <iostream>
#include <string>
#include <memory>
#include "Board.h"
#include "Rectangle.h"
#include "Circle.h"

int main() {
	Board board(80, 25);

	board.addShape(std::make_unique<Rectangle>(1, 5, 3, 'r', false, 10, 5)); //тимчасово для перевірки
	board.addShape(std::make_unique<Circle>(2, 50, 12, 'a', true, 5));
	
	std::string command;
	while (true) {
		std::cout << "> ";

		if (!std::getline(std::cin, command)) {
			break;
		}

		if (command == "draw") {
			board.draw();
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