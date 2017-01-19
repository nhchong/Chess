#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <string>
#include <vector>
#include "board.h"

class Controller {
 public:
  bool inGame = false;
  bool inSetup = false;
  bool quit = false;
  bool validBoard(Board &b); // returns whether or not the board is valid
  std::string play(Board &b);
  Board setup(Board &b);
  Board Import(Board &b, std::string file);
  Controller();
  ~Controller();
};

#endif
