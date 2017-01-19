#ifndef __KING_H__
#define __KING_H__
#include "piece.h"

class King: public Piece {
  bool moved = false;
 public:
  King(std::string colour, char name, const int x, const int y, Board *board);
  King(King &k);
  bool hasMoved() override;
  bool validMove(const int x2, const int y2);
  bool checkEveryMove(Board &b) override;
  void setMoved(bool b);
};

#endif
