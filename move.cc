#include "move.h"

Move::Move(int x1, int y1, int x2, int y2): x1{x1}, y1{y1}, x2{x2}, y2{y2} {}

void Move::setType(const char t) {type = t;}
