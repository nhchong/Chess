#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "board.h"
#include "piece.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
using namespace std;

vector<shared_ptr<Piece>> Board::defaultRow(string colour, int rowNum, int addIfBlack) {
 vector<shared_ptr<Piece>> row;
 auto k1 = make_shared<King>(colour, 'K' + addIfBlack, 4, rowNum, this);
 auto q1 = make_shared<Queen>(colour, 'Q' + addIfBlack, 3, rowNum, this);
 auto r1 = make_shared<Rook>(colour, 'R' + addIfBlack, 0, rowNum, this);
 auto r2 = make_shared<Rook>(colour, 'R' + addIfBlack, 7, rowNum, this);
 auto b1 = make_shared<Bishop>(colour, 'B' + addIfBlack, 2, rowNum, this);
 auto b2 = make_shared<Bishop>(colour, 'B' + addIfBlack, 5, rowNum, this);
 auto n1 = make_shared<Knight>(colour, 'N'+ addIfBlack, 1, rowNum, this);
 auto n2 = make_shared<Knight>(colour, 'N' + addIfBlack, 6, rowNum, this);
 row.emplace_back(r1);
 row.emplace_back(n1);
 row.emplace_back(b1);
 row.emplace_back(q1);
 row.emplace_back(k1);
 row.emplace_back(b2);
 row.emplace_back(n2);
 row.emplace_back(r2);
 return row;
}

Board::Board(vector<vector<shared_ptr<Piece>>> init): theBoard{init} {}

std::vector<std::vector<std::shared_ptr<Piece>>> Board::getBoard() {return theBoard;}

Board::Board() {
 vector<shared_ptr<Piece>> emptyRow;
 for(int i = 0; i < 8; i++) emptyRow.emplace_back(nullptr);
 for(int i = 0; i < 8; i++) {
  if(i == 0) theBoard.emplace_back(defaultRow("white", 0, 0));
  else if(i == 1) {
   vector<shared_ptr<Piece>> row2;
   for(int i = 0; i < 8; i++) {
    auto p1 = make_shared<Pawn>("white", 'P', i, 1, this);
    row2.emplace_back(p1);
   }
   theBoard.emplace_back(row2);
  }
  else if(i < 6) theBoard.emplace_back(emptyRow);
  else if(i == 6) {
   vector<shared_ptr<Piece>> row7;
   for(int i = 0; i < 8; i++) {
    auto p2 = make_shared<Pawn>("black", 'p', i, 6, this);
    row7.emplace_back(p2);
   }
   theBoard.emplace_back(row7);
  }
  else theBoard.emplace_back(defaultRow("black", 7, 32));
 }
}

Board::Board(const Board &other): currTurn{other.currTurn} {
 vector<shared_ptr<Piece>> emptyRow;
 for(int i = 0; i < 8; i++) emptyRow.emplace_back(nullptr);
 for(int i = 0; i < 8; ++i) theBoard.emplace_back(emptyRow);
 for(int i = 0; i < 8; ++i) {
  for(int j = 0; j < 8; ++j) {
   if (other.theBoard[i][j] != nullptr) {
    int ifblack;
    if (other.theBoard[i][j]->getColour() == "black") ifblack = 32;
    if (other.theBoard[i][j]->getType() == 'P' + ifblack) {
     theBoard[i][j] = make_shared<Pawn>(*dynamic_pointer_cast<Pawn>(other.theBoard[i][j]));
    }else if (other.theBoard[i][j]->getType() == 'R' + ifblack) {
     theBoard[i][j] = make_shared<Rook>(*dynamic_pointer_cast<Rook>(other.theBoard[i][j]));
    }else if (other.theBoard[i][j]->getType() == 'N' + ifblack) {
     theBoard[i][j] = make_shared<Knight>(*dynamic_pointer_cast<Knight>(other.theBoard[i][j]));
    }else if (other.theBoard[i][j]->getType() == 'B' + ifblack) {
     theBoard[i][j] = make_shared<Bishop>(*dynamic_pointer_cast<Bishop>(other.theBoard[i][j]));
    }else if (other.theBoard[i][j]->getType() == 'Q' + ifblack) {
     theBoard[i][j] = make_shared<Queen>(*dynamic_pointer_cast<Queen>(other.theBoard[i][j]));
    }else if (other.theBoard[i][j]->getType() == 'K' + ifblack) {
     theBoard[i][j] = make_shared<King>(*dynamic_pointer_cast<King>(other.theBoard[i][j]));
    }
   }
  }
 }
}

Board& Board::operator=(const Board &other) {
 Board temp{other};
 using std::swap;
 swap(theBoard, temp.theBoard);
 return *this;
}

Board::Board(Board &&other): theBoard{other.theBoard} {
 other.theBoard.clear();
}

Board& Board::operator=(Board &&other) {
 using std::swap;
 swap(theBoard, other.theBoard);
 return *this;
}

bool Board::checkCheck(string team) {
 int kingX;
 int kingY;
 // following loop finds coordinates of team's King
 for(int i = 0; i < 8; ++i) {
  for(int j = 0; j < 8; ++j) {
   if(theBoard[i][j] != nullptr && theBoard[i][j]->getColour() == team) {
    if(theBoard[i][j]->getType() == 'k' || theBoard[i][j]->getType() == 'K') {
     kingX = j;
     kingY = i;
     break;
    }
   }
  }
 }
 for(int i = 0; i < 8; ++i) {
  for(int j = 0; j < 8; ++j) {
   if(theBoard[i][j] != nullptr &&
      theBoard[i][j]->getColour() != team &&
      theBoard[i][j]->validMove(kingX, kingY) == true)
     return true;
   // team is in check if it is valid for opposite team to capture its King
  }
 }
 return false;
}


void Board::castleing(char king, int currX, int nextX, vector<vector<shared_ptr<Piece>>> origBoard) {
  if (king == 'K' && nextX == currX+2) {
    theBoard[0][5] = origBoard[0][7];
    theBoard[0][5]->setX(5);
    theBoard[0][7] = nullptr;
  } else if (king == 'K' && nextX == currX-2) {
    theBoard[0][3] = origBoard[0][0];
    theBoard[0][3]->setX(3);
    theBoard[0][0] = nullptr;
 } else if (king == 'k' && nextX == currX+2) {
    theBoard[7][5] = origBoard[7][7];
    theBoard[7][5]->setX(5);
    theBoard[7][7] = nullptr;
 } else if ('k' && nextX == currX-2) {
    theBoard[7][3]= origBoard[7][0];
    theBoard[7][3]->setX(3);
    theBoard[7][7] = nullptr;
 } 
} 

void Board::takeEnPassant(char pawn, int currY, int currX, int newX) {
  if ((pawn == 'P' || pawn == 'p') && (newX == currX+1 || newX == currX-1)) {
    theBoard[currY][newX] = nullptr;
  }
}

bool Board::move(int x1, int y1, int x2, int y2) { //x1.y1 cannot be a blank square, just check before use
// cout << "moving " << theBoard[y1][x1]->getType() << " at (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" <<  endl;
 if (theBoard[y1][x1] == nullptr) {
  setErrorCode(1);
  return false;
 }
 char Type = theBoard[y1][x1]->getType();
 string Colour = theBoard[y1][x1]->getColour();
 if (getTurn() == "white" && Colour == "black") {
  setErrorCode(2);
  return false;
 }
 if (getTurn() == "black" && Colour == "white") {
  setErrorCode(3);
   return false;
 }
 if (theBoard[y1][x1]->validMove(x2, y2) == false) {
  setErrorCode(4);
  return false;
 } 
 vector<vector<shared_ptr<Piece>>> origBoard = theBoard;
 theBoard[y2][x2] = theBoard[y1][x1];
 theBoard[y1][x1] = nullptr;
 theBoard[y2][x2]->setX(x2);
 theBoard[y2][x2]->setY(y2);
 if (checkCheck(theBoard[y2][x2]->getColour())) {
  theBoard[y1][x1] = theBoard[y2][x2];
  theBoard[y2][x2] = nullptr;
  theBoard[y1][x1]->setX(x1);
  theBoard[y1][x1]->setY(y1);
  setErrorCode(5);
  return false;
 }
 castleing(Type, x1, x2, origBoard);
 if (origBoard[y2][x2] == nullptr) {
  takeEnPassant(Type, y1, x1, x2);
 }
 if (Type == 'P') {
  if (y2 != y1+2) { 
   // if it's a white pawn and has moved two spaces on it's first move then it can be taken en passant
   theBoard[y2][x2]->canBeEP = false; 
  } else {
   theBoard[y2][x2]->canBeEP = true;
  }
 }
 if (Type == 'p') {
   if (y2 != y1-2) {
    theBoard[y2][x2]->canBeEP = false; // it can be taken enpassant otherwise
   } else {
    theBoard[y2][x2]->canBeEP = true;
   }
 }
 if (Type == 'k' || Type == 'K' || Type == 'r' || Type == 'R' || Type == 'p' || Type == 'P') {
  theBoard[y2][x2]->setMoved(true);
 }
 if (Colour == "white") changeTurns("black"); 
 if (Colour == "black") changeTurns("white");
 return true;
}

bool Board::moveTransform(int x1, int y1, int x2, int y2, char type) {
 if (theBoard[y1][x1] == nullptr || theBoard[y1][x1]->validMove(x2, y2) == false) {
  return false;
 }
 int caseSwap = 0;
 string moverColour = theBoard[y1][x1]->getColour();
 if (moverColour == "black") caseSwap = 32;
 if (type == 'Q') {
  theBoard[y2][x2] = make_shared<Queen>(moverColour, 'Q'+caseSwap, x2, y2, this);
 } else if (type == 'R') {
  theBoard[y2][x2] = make_shared<Rook>(moverColour, 'R'+caseSwap, x2, y2, this);
 } else if (type == 'N') {
  theBoard[y2][x2] = make_shared<Knight>(moverColour, 'N'+caseSwap, x2, y2, this);
 } else if (type == 'B') {
  theBoard[y2][x2] = make_shared<Bishop>(moverColour, 'B'+caseSwap, x2, y2, this);
 } else { 
  return false; 
 }
 string Colour = theBoard[y2][x2]->getColour();
 if (Colour == "white") changeTurns("black"); 
 if (Colour == "black") changeTurns("white");
 return true;
}


// this function returns who's move it is
string Board::getTurn() {
  return currTurn;
}

// Changes who's turn it is
void Board::changeTurns(string team) {
  currTurn = team;
}

bool Board::checkMate(string team) {
  Board tempBoard{theBoard};
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (theBoard[i][j] != nullptr) {
        if (theBoard[i][j]->getColour() == team && 
          theBoard[i][j]->checkEveryMove(tempBoard) == true) {
          return false;
        }
      }
    }
  }
  return true;
}

// This method returns whether the game is over or not
// A game is over if no move can be made and a stalemate is encountered
/*bool Board::gameOver() {
 for(int i = 0; i < 8; i++) {
  for(int j = 0; j < 8; j++) {
   if(theBoard[i][j] != nullptr && theBoard[i][j]->checkEveryMove() == true) return false;
  }
 }
 return true;
}*/

// This method prints the board
void Board::printBoard() {
 int currCol = 8;
 for(int i = 7; i >= 0; --i) {
  cout << currCol << " ";
  --currCol;
  for(int j = 0; j < 8; j++) {
   if(theBoard[i][j] == nullptr) {
    if(i%2 == 1) {
     if (j%2 == 0) cout << "_";
     else cout << " ";
    } else {
     if (j%2 == 0) cout << " ";
     else cout << "_";
    }
   } else {
    cout << theBoard[i][j]->getType();
   }
  }
  cout << endl;
 }
 cout << endl << "  abcdefgh" << endl;
}

// This method creates a piece as determined by type and inserts it at x1,y1
// If theere is already a piece at x1,y1, it replaces it
void Board::insertPiece(char type, int x1, int y1) {
  if (type == 'r') {
    auto newRook = make_shared<Rook>("black", type, x1, y1, this);
    theBoard[y1][x1] = newRook;
  } else if (type == 'n') {
    auto newKnight = make_shared<Knight>("black", type, x1, y1, this);
    theBoard[y1][x1] = newKnight;
  } else if (type == 'b') {
    auto newBishop = make_shared<Bishop>("black", type, x1, y1, this);
    theBoard[y1][x1] = newBishop;
  } else if (type == 'q') {
    auto newQueen = make_shared<Queen>("black", type, x1, y1, this);
    theBoard[y1][x1] = newQueen;
  } else if (type == 'k') {
    auto newKing = make_shared<King>("black", type, x1, y1, this);
    theBoard[y1][x1] = newKing;
  } else if (type == 'p') {
    auto newPawn = make_shared<Pawn>("black", type, x1, y1, this);
    theBoard[y1][x1] = newPawn;
  } else if (type == 'R') {
    auto newRook = make_shared<Rook>("white", type, x1, y1, this);
    theBoard[y1][x1] = newRook;
  } else if (type == 'N') {
    auto newKnight = make_shared<Knight>("white", type, x1, y1, this);
    theBoard[y1][x1] = newKnight;
  } else if (type == 'B') {
    auto newBishop = make_shared<Bishop>("white", type, x1, y1, this);
    theBoard[y1][x1] = newBishop;
  } else if (type == 'Q') {
    auto newQueen = make_shared<Queen>("white", type, x1, y1, this);
    theBoard[y1][x1] = newQueen;
  } else if (type == 'K') {
    auto newKing = make_shared<King>("white", type, x1, y1, this);
    theBoard[y1][x1] = newKing;
  } else if (type == 'P') {
    auto newPawn = make_shared<Pawn>("white", type, x1, y1, this);
    theBoard[y1][x1] = newPawn;
  } else if (type == '0') {
    theBoard[y1][x1] = nullptr;
  }
}

void Board::setErrorCode(int code) {
  errorCode = code;
}

int Board::getErrorCode() {
  return errorCode;
}

void Board::printError(int code) {
  if (code == 1) {
    cout << "There is no piece at this position. Please enter another move." << endl;
  } else if (code == 2) {
    cout << "It's not black's turn. White team, please make a move." << endl;
  } else if (code == 3) {
    cout << "It's not white's turn. Black team, please make a move." << endl;
  } else if (code == 4) {
    cout << "That is not a valid move. Please enter another move." << endl;
  } else {
    cout << "That move puts you in check. Please enter another move." << endl;
  }
}

Board::~Board() {}
