#include <iostream>
#include <string>
#include "Board.h"

int main() {
	Board board(80, 25);

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