#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>


class Board;

class Piece {
 protected:
  std::string colour;
  char name;
  int x;
  int y;
  // Board *board;
 public:
  Board *board;
  char getType();
  virtual void setEnPassant(bool b);
  virtual bool getCanBeEP();
  virtual bool checkEnPassant(int x1, int y1);
  std::string getColour();
  virtual bool validMove(const int x1, const int y2) = 0;
  virtual bool hasMoved();
  bool canBeEP = false;
  virtual void setMoved(bool b);
  void setX(int x2);
  void setY(int y2);
  bool validDestination(const int x1, const int y2);
  // this check if the desired move covers basic validity such as if the 
  // desitination is on the board and if there is a piece on the destination
  // square that it's a piece from the opposite team
  void printSquare();
  virtual bool checkEveryMove(Board &b) = 0;
  Piece(std::string colour, char name, const int x, const int y, Board *board);
  Piece(Piece &p);
  ~Piece();
};

#endif
