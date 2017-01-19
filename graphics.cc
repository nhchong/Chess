#include "graphics.h"
#include "board.h"
#include <vector>
#include "piece.h"
#include <sstream>
#include <string>

Graphics::Graphics() {
  int dim = 500/8;
  for (int i = 0; i < 8; ++i) {
   for (int j = 0; j < 8; ++j) {
    if ((i+j)%2 ==0) {xw.fillRectangle(i*dim, j*dim, dim, dim, Xwindow::White);}
    else {xw.fillRectangle(i*dim, j*dim, dim, dim, Xwindow::Black);}
   }
  }
}

void Graphics::update(Board &b) {
  int dim = 500/8;
  for (int i = 0; i < 8; ++i) {
   for (int j = 0; j < 8; ++j) {

    if ((i+j)%2 == 0) {xw.fillRectangle(i*dim, j*dim, dim, dim, Xwindow::White);}
    else {xw.fillRectangle(i*dim, j*dim, dim, dim, Xwindow::Black);}

    if (b.getBoard()[7-j][i] != nullptr) {
     std::stringstream ss;
     std::string s;
     ss << b.getBoard()[7-j][i]->getType();
     ss >> s;
     xw.drawString((i+0.5)*dim, (j+0.5)*dim, s, Xwindow::Red);
    }

   }
  }
}

