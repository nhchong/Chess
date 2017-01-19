#include "board.h"
#include "piece.h"
#include <string>
#include <iostream>

using namespace std;


Piece::Piece(string colour, char name, const int x, const int y, Board *board): 
		     colour {colour}, name {name}, x {x}, y {y}, board {board} {}

Piece::Piece(Piece &p):colour{p.colour}, name{p.name}, x{p.x}, y{p.y}, board{p.board} {}

bool Piece::validDestination(const int x2, const int y2) {
    int maxWidth = 7;
    int maxHeight = 7;
    int minHeight = 0;
    int minWidth = 0;
    if (x == x2 && y == y2) {
		// if the destination is it's current position
		return false;
	}
    if (x2 > maxWidth || x2 < minWidth || y2 > maxHeight || y2 < minWidth) {
    	// if the destination is outside the board limits
    	return false;
	}
	if (board->getBoard()[y2][x2] != nullptr && 
		board->getBoard()[y2][x2]->getColour() == colour) { 
    	// if there is a piece at the destination and it is the same colour as the piece,
    	return false;
    } else {
    	return true;
    }
}

void Piece::setEnPassant(bool b) {}

bool Piece::checkEnPassant(int x1, int y1) {
 return false;
}

bool Piece::getCanBeEP() {
 return false;
} 

void Piece::setMoved(bool b) {}

bool Piece::hasMoved() {
 return false;
}

void Piece::setX(int x2) {
 x = x2;
}

void Piece::setY(int y2) {
 y = y2;
}

Piece::~Piece() {}

void Piece::printSquare() {
	cout << getType();
}

char Piece::getType() {
  return name;
}

string Piece::getColour() {
  return colour;
}
