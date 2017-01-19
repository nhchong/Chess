#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"

class Pawn: public Piece {
  bool moved = false;
  bool canBeEP = true; // represents whether or not a pawn can be taken en passant
 public:
  Pawn(std::string colour, char name, const int x, const int y, Board *board);
  Pawn(Pawn &p);
  bool hasMoved() override;
  bool checkEnPassant(const int x2, const int y2) override; 
  // checks if the move tryign to be made is an en passant
  bool getCanBeEP() override;
  bool validMove(const int x2, const int y2);
  bool checkEveryMove(Board &b);
  void setMoved(bool b) override;
  void setEnPassant(bool b) override;
};

#endif


