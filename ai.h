#ifndef __AI_H__
#define __AI_H__
#include <string>

class Board;

class AI {
  const int level;
  const std::string team;
  std::string enemy;
 public:
  AI(int level, std::string team);
  bool canBeChecked(const Board &b);
  int numValidMoves(const Board &b);
  void makeMove(Board *b);
};

#endif
