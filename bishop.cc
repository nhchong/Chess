#include "bishop.h"
#include "board.h"
#include <iostream>
using namespace std;

Bishop::Bishop(string colour, char name, const int x, const int y, Board *board):
           Piece(colour, name, x, y, board) {}


// this function returns true if there are no obstructions and false if there are
bool Bishop::checkObstructions(const int x2, const int y2) {
	int currX;
	int currY;
	if (x < x2) {
		if (y < y2) {	// bishop is moving upward to the right
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
		} else if (y > y2) {	// bishop is moving downward toward the right
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
		if (y < y2) {	// bishop is moving upward to the left
			currX = x-1;
			currY = y+1;
			while (currX > x2 && currY < y2) {
        cout << "In the while loop" << endl;
				if (board->getBoard()[currY][currX] != nullptr) {
					return false;
				} else {
					--currX;
					++currY;
				}
			}
		} else if (y > y2) {	// bishop is moving downward toward the left
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
	} 	// don't have to check if x2 == x b/c that is done in validMove
	return true;
}

bool Bishop::validMove(const int x2, const int y2) {
   	if (!validDestination(x2, y2)) { 
      // cout << "returning false becuase not a valid destination" << endl;
      return false; 
    } 
    if (!checkObstructions(x2, y2)) { 
     //  cout << "returning false because there are obstructions (bishop)" << endl;
      return false; 
    }
    if (x == x2 || y == y2) { 
      // cout << "returning false because either x or y are the same" << endl;
      return false; }	// this guarentees that it's moving on a diagonal
    if (y2 > y) {						          	// --
    	if (x2 > x) {				          		//  |
    		return ((y2 - y) == (x2 - x));  //  |
    	} else {	         			        	//  |
    		return ((y2 - y) == (x - x2));	//  |
    	}									                //  | ---- Check if valid diagonal move
    } else {					             			//  |
    	if (x2 > x) {					          	//  |
    		return ((y - y2) == (x2 - x));	//  |
    	} else {		            	        //  |
    		return ((y - y2) == (x - x2));	//  |
    	}								                 	// --
    }
}

bool Bishop::checkEveryMove(Board &b) {
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
  return false;
}
