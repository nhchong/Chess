#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

class Bishop: public Piece {
 public:
  Bishop(std::string colour, char name, const int x, const int y, Board *board);
  bool checkObstructions(const int x2, const int y2); // checks for any obstructions between current position and possible new destination
  bool validMove(const int x2, const int y2);
  bool checkEveryMove(Board &b);
  void printSquare();
};

#endif

