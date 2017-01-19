#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(string colour, char name, const int x, const int y, Board *board):
           Piece(colour, name, x, y, board) {}


bool Knight::validMove(const int x2, const int y2) {
	if (!validDestination(x2, y2)) {
		return false;
	} else if (y2 == y+1 || y2 == y-1) {
		return (x2 == x+2 || x2 == x-2);
	} else if (x2 == x+1 || x2 == x-1) {
		return (y2 == y+2 || y2 == y-2);
	} else {
		return false;
	}
}

bool Knight::checkEveryMove(Board &b) {
  for (int i = -2; i <= 2; i += 4) {
    for (int j = -1; j <= 1; j += 2) {
      if ((x+i >= 0 && x+i < 8 && y+j >=0 && y+j < 8 && b.move(x,y,x+i,y+j)) ||
          (x+j >= 0 && x+j < 8 && y+i >=0 && y+i < 8 && b.move(x,y,x+j,y+i)))
	return true;
    }
  }
  return false;
}
