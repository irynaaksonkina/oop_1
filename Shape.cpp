#include "Shape.h"

Shape::Shape(int id, int x, int y, char color, bool filled)
	: id(id), x(x), y(y), color(color), filled(filled) {

}

int Shape::getId() const {
	return id;
}

int Shape::getX() const {
	return x;
}

int Shape::getY() const {
	return y;
}

char Shape::getColor() const {
	return color;
}

bool Shape::isFilled() const {
	return filled;
}

void Shape::paint(char newColor) {
	color = newColor;
}

void Shape::moveTo(int newX, int newY) {
	x = newX;
	y = newY;
}