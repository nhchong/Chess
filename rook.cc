#include "rook.h"
#include "board.h"
using namespace std;

Rook::Rook(string colour, char name, const int x, const int y, Board *board):
           Piece(colour, name, x, y, board) {}

Rook::Rook(Rook &r): Piece(r), moved{r.moved} {}

bool Rook::checkObstructions(const int x2, const int y2) {
	int currX;
	int currY;
	if (y == y2) {	
		if (x < x2) {	// Rook is moving to the right
			currX = x+1;
			while (currX < x2) {
				if (board->getBoard()[y][currX] != nullptr) {
					return false;
				} else {
					++currX;
				}
			}
		} else if (x > x2) {	// Rook is moving to the left
			currX = x-1;
			while (currX > x2) {
				if (board->getBoard()[y][currX] != nullptr) {
					return false;
				} else {
					--currX;
				}
			}
		}
	} else if (x == x2) {	
		if (y < y2) {	// Rook is moving to upward
			currY = y+1;
			while (currY < y2) {
				if (board->getBoard()[currY][x] != nullptr) {
					return false;
				} else {
					++currY;
				}
			}
		} else if (y > y2) {	// Rook is moving downward
			currX = y-1;
			while (currY > y2) {
				if (board->getBoard()[currY][x] != nullptr) {
					return false;
				} else {
					--currY;
				}
			}
		}
	}
	return true;
}

bool Rook::validMove(const int x2, const int y2) {
	if (!validDestination(x2, y2)) { return false; } 
	if (y != y2) {
		if (x != x2) {
			return false;
		}
	}
	if (x != x2) {
		if (y != y2) {
			return false;
		}
	}
    if (!checkObstructions(x2, y2)) { return false; } 
    return true; // all conditions hold so return true
}

bool Rook::hasMoved() {
	return moved;
}

bool Rook::checkEveryMove(Board &b) {
  int n = 1;
  for (int i = -1; i <= 1; ++i) {
    n = 1;
    while (x+n*i >= 0 && x+n*i < 8) {
      if (b.move(x,y,x+n*i,y)) { return true; }
      if (b.getBoard()[y][x+n*i] != nullptr) break;
      ++n;
    }
    n = 1;
    while (y+n*i >= 0 && y+n*i < 8) {
      if (b.move(x,y,x,y+n*i)) { return true; }
      if (b.getBoard()[y+n*i][x] != nullptr) break;
      ++n;
    }
  }
  return false;
}

void Rook::setMoved(bool b) { moved = b; }

