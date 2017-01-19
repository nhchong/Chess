#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include "window.h"

class Board;

class Graphics {
  Xwindow xw;
 public:
  Graphics();
  void update(Board &b);
};

#endif
