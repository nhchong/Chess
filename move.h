#ifndef __MOVE_H__
#define __MOVE_H__

struct Move {
  int x1, y1, x2, y2;
  char type = '0';  
  Move(int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);
  void setType(const char t);
};

#endif
