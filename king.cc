#include "king.h"
#include "board.h"
#include <iostream>

using namespace std;

King::King(string colour, char name, const int x, const int y, Board *board):
           Piece(colour, name, x, y, board) {}

King::King(King &k): Piece(k), moved{k.moved} {}

bool King::validMove(const int x2, const int y2) {
  if (!validDestination(x2, y2)) { 
    return false; 
  } 
  if (x2 == x+1 || x2 == x-1) {
    return (y2 == y+1 || y2 == y-1 || y2 == y);
  } else if (x == x2) {
    return (y2 == y+1 || y2 == y-1);
  } else if (x2 == x+2) {            // trying to castle to the right
      if (getColour() == "white") {
      if (board->getBoard()[0][7] != nullptr && 
        board->getBoard()[0][7]->getColour() == "white" && 
        board->getBoard()[0][7]->getType() == 'R' && 
        !board->getBoard()[0][7]->hasMoved() && !hasMoved()) {
        for (int currX = 5; currX < 7; ++currX) {
          // check to see if no pieces in between
          if (board->getBoard()[0][currX] != nullptr) {
            return false;
          }
        }
        return true;
      }
    } else {
      if (board->getBoard()[7][7] != nullptr && 
        board->getBoard()[7][7]->getColour() == "black" && 
        board->getBoard()[7][7]->getType() == 'r' && 
        !board->getBoard()[7][7]->hasMoved() && !hasMoved()) {
        for (int currX = 5; currX < 7; ++currX) {
          // check to see if no pieces in between
          if (board->getBoard()[7][currX] != nullptr) {
            return false;
          }
        }
        return true;
      }
    }
  } else if (x2 == x-2) {            // trying to castle to the left
    if (getColour() == "white") {
      if (board->getBoard()[0][0] != nullptr && 
        board->getBoard()[0][0]->getColour() == "white" && 
        board->getBoard()[0][0]->getType() == 'R' &&
        board->getBoard()[0][0]->hasMoved() && !hasMoved()) {
        for (int currX = 3; currX > 1; --currX) {
          // check to see if no pieces in between
          if (board->getBoard()[0][currX] != nullptr) {
            return false;
          }
        }
        return true;
      }
    } else {
      if (board->getBoard()[7][0] != nullptr && 
        board->getBoard()[7][0]->getColour() == "black" && 
        board->getBoard()[7][0]->getType() == 'r' && 
        !board->getBoard()[7][0]->hasMoved() && !hasMoved()) {
        for (int currX = 3; currX > 1; --currX) {
          // check to see if no pieces in between
          if (board->getBoard()[7][currX] != nullptr) {
            return false;
          }
        }
        return true;
      }
    }
  }
  // Never have to check whether or not the King is in the right position because
  // !moved is true only if the King is in the correct position
  return false;
}

bool King::hasMoved() {
  return moved;
}

bool King::checkEveryMove(Board &b) {
  if (b.move(x,y,x+2,y) || b.move(x,y,x-2,y)) { return true; }
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (j != 0 || i != 0) {
  if (b.move(x,y,x+i,y+j)) { return true; }
      }
    }
  }
  return false;
}

void King::setMoved(bool b) { moved = b; }

