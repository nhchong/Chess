#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>

class Piece;

class Board {
  std::string currTurn = "white";
  std::vector<std::vector<std::shared_ptr<Piece>>> theBoard;
  int errorCode = 0;
 public: 
  Board();
  Board(std::vector<std::vector<std::shared_ptr<Piece>>> init);
  Board(const Board &other);
  Board &operator=(const Board &other);
  Board(Board &&other);
  Board &operator=(Board &&other);
  std::vector<std::vector<std::shared_ptr<Piece>>> getBoard();
  std::vector<std::shared_ptr<Piece>> defaultRow(std::string colour, int rowNum, int addIfBlack);
  int getErrorCode();
  void setErrorCode(int code);
  void printError(int code);
  void changeTurns(std::string team); // changes the turn from one team to the other
  std::string getTurn(); // return who's turn it is
  bool checkCheck(std::string team);
  bool checkMate(std::string team);
  bool move(int x1, int y1, int x2, int y2);
  bool moveTransform(int x1, int y1, int x2, int y2, char type);
  void castleing(char king, int currX, int nextX, std::vector<std::vector<std::shared_ptr<Piece>>> origBoard);
  void takeEnPassant(char pawn, int currY, int currX, int newX);
  bool gameOver();
  void printBoard();
  void insertPiece(char type, int x1, int y1);
  ~Board();
};

#endif
