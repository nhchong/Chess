#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

class Rook: public Piece {
  bool moved = false;
 public:
  Rook(std::string colour, char name, const int x, const int y, Board *board);
  Rook(Rook &r);
  bool hasMoved() override; // returns whether or not the rook has moved
  bool checkObstructions(const int x2, const int y2); // checks for any obstructions between current position and possible new destination
  bool validMove(const int x2, const int y2);
  bool checkEveryMove(Board &b);
  void setMoved(bool b);
};

#endif

