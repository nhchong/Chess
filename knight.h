#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight: public Piece {
 public:
  Knight(std::string colour, char name, const int x, const int y, Board *board);
  bool validMove(const int x2, const int y2);
  bool checkEveryMove(Board &b);
};

#endif

