#include "pawn.h"
#include "board.h"
#include <iostream>

using namespace std;

Pawn::Pawn(string colour, char name, const int x, const int y, Board *board):
          Piece(colour, name, x, y, board) {}

Pawn::Pawn(Pawn &p): Piece(p), moved{p.moved} {}

bool Pawn::checkEnPassant(const int x2, const int y2) {
	if (getColour() == "white") {
		if (y == 4 && y2 == y+1) {	// tryign to en passant to the right
			return (board->getBoard()[y][x2] != nullptr && 
				board->getBoard()[y][x2]->getType() == 'p' && 
				board->getBoard()[y][x2]->getColour() == "black" && 
				board->getBoard()[y][x2]->canBeEP);
		} else {
			return false;
		}
	} else {
		if (y == 3 && y2 == y-1) {	// tryign to en passant to the right;
      cout << board->getBoard()[y][x2]->canBeEP << endl;
			return (board->getBoard()[y][x2] != nullptr && 
				board->getBoard()[y][x2]->getType() == 'P' && 
				board->getBoard()[y][x2]->getColour() == "white" && 
				board->getBoard()[y][x2]->canBeEP);
		} else {
			return false;
		}
	}
}

bool Pawn::getCanBeEP() {
 return canBeEP;
}

bool Pawn::validMove(const int x2, const int y2) {
  if (x == x2 && y == y2) { return false; }
	if (x2 > 7|| x2 < 0 || y2 > 7 || y2 < 0) { 
		return false;
	}
	if (x2 == x+1 || x2 == x-1) { // trying to capture regularly or through enpassant
		if ((getColour() == "white" && y2 == y+1) || (getColour() == "black" && y2 == y-1)) {	
			if (board->getBoard()[y2][x2] != nullptr) { 
				return (board->getBoard()[y2][x2]->getColour() != getColour());
			} else {
				return checkEnPassant(x2, y2);
			}
		}
	} else if (x2 == x) {	// trying to promote
		if (getColour() == "white") {
			if ((y2 == y+1) || (y2 == y+2 && !moved && board->getBoard()[y+1][x] == nullptr)) { 
				return board->getBoard()[y2][x2] == nullptr;
			}
		} else {
			if ((y2 == y-1) || (y2 == y-2 && !moved && board->getBoard()[y-1][x] == nullptr)) {
				return  board->getBoard()[y2][x2] == nullptr;
			}
		}
  }
	return false;
}

void Pawn::setEnPassant(bool b) {
	canBeEP = b;
}

bool Pawn::hasMoved() {
	return moved;
}

bool Pawn::checkEveryMove(Board &b) {
  int n;
  if (getColour() == "black") {
    n = -1;
  } else { n = 1; }
  for (int i = -1; i <= 1; ++i) {
    if (b.move(x,y,x+i,y+n)) { return true; }
  }
  if (b.move(x,y,x,y+2*n)) { return true; }
  return false;
}

void Pawn::setMoved(bool b) { moved = b; }

