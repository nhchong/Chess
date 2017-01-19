#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "controller.h"
#include "board.h"
#include "graphics.h"
#include "ai.h"
#include "piece.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "rook.h"
#include "pawn.h"
using namespace std;

Controller::Controller() {}

Controller::~Controller() {}

// This method determines whether a board is valid or not
// A baord is valid if it has a white and black king, both kings are not in
//  check and if there are no pawns in the first or last row
bool Controller::validBoard(Board &b) {
	int numOfWhiteKings = 0;
	int numOfBlackKings = 0;
	bool whiteKing = false;
	bool blackKing = false;
	bool whiteInCheck = false;
	bool blackInCheck = false;
	bool noPawnsOnFirstAndLast = true;
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
      	if (whiteInCheck || blackInCheck) return false;
    		if (b.getBoard()[row][col] == nullptr) continue;
	  		if (b.getBoard()[row][col]->getType() == 'K') {
				whiteKing = true;
				++numOfWhiteKings;
				if (numOfWhiteKings > 1) return false;
				// want to check if the number of Kings is > 1 before checking
				// check because don't want to run checkCheck with two kings
 				whiteInCheck = b.checkCheck("white");
	  		} else if (b.getBoard()[row][col]->getType() == 'k') {
				blackKing = true;
				blackInCheck = b.checkCheck("black");
				++numOfBlackKings;
				if (numOfBlackKings > 1) return false;
			} else if ((b.getBoard()[row][col]->getType() == 'p' ||
        b.getBoard()[row][col]->getType() == 'P') && (row == 0 || row == 7)) {
				noPawnsOnFirstAndLast = false;
			}
		}
	}
  // cout << whiteKing << blackKing << noPawnsOnFirstAndLast<< endl;
	return (whiteKing && blackKing && noPawnsOnFirstAndLast);
}



int convertColToInt(char column) {
	return column-97;
}

int convertRowToInt(char row) {
	string rowAsString(1, row);
	istringstream stringToInt{rowAsString};
	int rowAsInt;
	stringToInt >> rowAsInt;
	return rowAsInt-1;
}

// this method handles all game flow
string Controller::play(Board &b) {
 Graphics g;
 g.update(b);
 b.printBoard();
 string whitePlayer;
 string blackPlayer;
 int level;
 cin >> whitePlayer;
 shared_ptr<AI> white = nullptr;
 if (whitePlayer == "Computer") {
  cin >> level;
  white = make_shared<AI>(level,"white");
 }
 cin >> blackPlayer;
 shared_ptr<AI> black = nullptr;
 if (blackPlayer == "Computer") {
  cin >>level;
  black = make_shared<AI>(level, "black");
 }
 while (!quit) {
   if (b.getTurn() == "white" && white != nullptr) {
    white->makeMove(&b);
    b.printBoard();
   } else if (b.getTurn() == "black" && black != nullptr) {
    black->makeMove(&b);
    b.printBoard();
   } else {
    string command;
    cin >> command;
    if (command == "move") {
      string currPos;
      string newPos;
      cin  >> currPos;
      cin  >> newPos;
      int currCol = convertColToInt(currPos[0]);
      int currRow = convertRowToInt(currPos[1]);
      int newCol = convertColToInt(newPos[0]);
      int newRow = convertRowToInt(newPos[1]);
      if (b.getBoard()[currRow][currCol]->getType() == 'P' && newRow == 7) {
       string newPiece;
       cin >> newPiece;
       if (b.moveTransform(currCol, currRow, newCol, newRow, newPiece[0])) {
         b.printBoard();
       }
      } else if (b.getBoard()[currRow][currCol]->getType() == 'p' && newRow == 0) {
        string newPiece;
        cin >> newPiece;
        if (b.moveTransform(currCol, currRow, newCol, newRow, newPiece[0])) {
          b.printBoard();
        }
      } else {
        if (b.move(currCol, currRow, newCol, newRow)) {
         // if move returns true, then the move has been made and you should print
         b.printBoard();
       } else { // check for what error occured
       	  b.printError(b.getErrorCode());
       }
     }
     /*if (b.getTurn() == "black") {
     	if (b.checkmate("black")) { 
     	   cout << "checkmate" << endl
     	}
     } else {
     	if (b.checkmate("white")) {
     		cout << "checkmate" << endl;
     	}
     }*/
    } else if (command == "resign") {
       if (b.getTurn() == "black") {
       	return "white";
       } else {
       	return "black";
       }
    } else {
       cout << "Please enter a move command or 'resign'" << endl;
    }
  }
  g.update(b);
 }
}

Board Controller::Import(Board &b, string file) {
 inSetup = true;
 for (int i = 0; i < 8; ++i) {
	for (int j = 0; j < 8; ++j) {
	  	 b.insertPiece('0', i, j);
	}
 }
 string command;
 ifstream fs{file};
 while (fs >> command) {
	if (command == "+") {
		string type;
		string addPosition;
		fs >> type;
		fs >> addPosition;
		int col = convertColToInt(addPosition[0]);
 		int row = convertRowToInt(addPosition[1]);
		char typeAsChar = type[0];
		if (col < 8 && row < 8) {
			b.insertPiece(typeAsChar, col, row);
   		    // b.printBoard();
		} else {
			// cout << "The given position is not valid" << endl;
		}
	} else if (command == "-") {
		string removePosition;
		fs >> removePosition;
		int col = convertColToInt(removePosition[0]);
   		int row = convertRowToInt(removePosition[1]);
		if (col < 8 && row < 8) {
		    b.insertPiece('0', col, row);
    	    // b.printBoard();
		} else {
			// cout << "The given position is not valid" << endl;
		}
	} else if (command == "=") {
		string newColour;
		fs >> newColour;
		b.changeTurns(newColour);
	} else if (command == "done") {
		if (validBoard(b)) {
			inSetup == false;
	        break;
		} else {
			cout << "You have not entered a valid Board. Please change it." << endl;
		}
	} else if (command == "setup") {
    continue;
  }  else {
		cout << "That is not a valid setup command. Please enter another." << endl;
	}
 }
 return b;
}

Board Controller::setup(Board &b) {
 inSetup = true;
 for (int i = 0; i < 8; ++i) {
	for (int j = 0; j < 8; ++j) {
	  	 b.insertPiece('0', i, j);
	}
 }
 string command;
 while (inSetup) {
	cin >> command;
	if (command == "+") {
		string type;
		string addPosition;
		cin >> type;
		cin >> addPosition;
		int col = convertColToInt(addPosition[0]);
 		int row = convertRowToInt(addPosition[1]);
		char typeAsChar = type[0];
		if (col < 8 && row < 8) {
			b.insertPiece(typeAsChar, col, row);
   		    b.printBoard();
		} else {
			cout << "The given position is not valid" << endl;
		}
	} else if (command == "-") {
		string removePosition;
		cin >> removePosition;
		int col = convertColToInt(removePosition[0]);
   		int row = convertRowToInt(removePosition[1]);
		if (col < 8 && row < 8) {
		    b.insertPiece('0', col, row);
    	    b.printBoard();
		} else {
			cout << "The given position is not valid" << endl;
		}
	} else if (command == "=") {
		string newColour;
		cin >> newColour;
		b.changeTurns(newColour);
	} else if (command == "done") {
		if (validBoard(b)) {
			inSetup == false;
	        break;
		} else {
			cout << "You have not entered a valid Board. Please change it." << endl;
		}
	} else {
		cout << "That is not a valid setup command. Please enter another." << endl;
	}
 }
 return b;
}
