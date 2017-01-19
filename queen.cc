#include "queen.h"
#include "board.h"
#include <iostream>

using namespace std;

Queen::Queen(string colour, char name, const int x, const int y, Board *board):
           Piece(colour, name, x, y, board) {}


// this function returns true if there are no obstructions and false if there are
bool Queen::checkObstructions(const int x2, const int y2) {
	int currX;
	int currY;
	if (x < x2) {
		if (y < y2) {	// Queen is moving upward to the right
			currX = x+1;
			currY = y+1;
			while (currX < x2 && currY < y2) {
				if (board->getBoard()[currY][currX] != nullptr) {
					return false;
				} else {
					++currX;
					++currY;
				}
			}
		} else if (y > y2) {	// Queen is moving downward toward the right
			currX = x+1;
			currY = y-1;
			while (currX < x2 && currY > y2) {
				if (board->getBoard()[currY][currX] != nullptr) {
         	return false;
				} else {
					++currX;
					--currY;
				}
			}
		}
	} else if (x > x2) {
		if (y < y2) {	// Queen is moving upward to the left
			currX = x-1;
			currY = y+1;
			while (currX > x2 && currY < y2) {
				if (board->getBoard()[currY][currX] != nullptr) {
					return false;
				} else {
					--currX;
					++currY;
				}
			}
		} else if (y > y2) {	// Queen is moving downward toward the left
			currX = x-1;
			currY = y-1;
			while (currX < x2 && currY < y2) {
				if (board->getBoard()[currY][currX] != nullptr) {
					return false;
				} else {
					--currX;
					--currY;
				}
			}
		}
	} else {
		if (y < y2) {	// Queen is moving directly upward
			currY = y+1;
			while (currY < y2) {
				if (board->getBoard()[currY][x] != nullptr) {
					return false;
				} else {
					++currY;
				}
			}
		} else if (y > y2) {	// Queen is moving directly downward
			currY = y-1;
			while (currY < y2) {
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

bool Queen::validMove(const int x2, const int y2) {
	if (!validDestination(x2, y2)) { return false; }
  if (!checkObstructions(x2, y2)) { return false; } 
    if (y2 > y) {						           	// --
    	if (x2 > x) {					           	//  |
    		return ((y2 - y) == (x2 - x));  //  |
    	} else if (x2 < x){	         			//  |
    		return ((y2 - y) == (x - x2));	//  |
    	} else {                          //  |
        return true;                    //  |
      }								                 	//  | ---- Check if valid diagonal move
    } else if (y2 < y) {					      //  |
    	if (x2 > x) {						          //  |
    		return ((y - y2) == (x2 - x));	//  |
    	} else if (x2 < x) {		    	    //  |
    		return ((y - y2) == (x - x2));	//  |
    	} else {                          //  |
        return true;                    //  |
      }								                 	// -- 
    } 
  return true; 
  // will return true if moving in horizontal straight line
}

bool Queen::checkEveryMove(Board &b) {
  int n = 1;
  for (int i = -1; i <= 1; i += 2) {
    for (int j = -1; j <= 1; j += 2) {
      while ((x+n*i >= 0 && x+n*i <= 7 && y+n*j >= 0 && y+n*j <= 7) ||
             b.getBoard()[y+n*j][x+n*i] == nullptr ||
             b.getBoard()[y+n*j][x+n*i]->getColour() != getColour()) {
        if (b.move(x,y,x+n*i,y+n*j)) {return true;}
        n++;
      }
      n = 1;
    }
    n = 1;
  }
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
