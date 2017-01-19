#include "ai.h"
#include "board.h"
#include "piece.h"
#include "move.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

AI::AI(int level, string team): level{level}, team{team} {
  enemy = (team == "white"? "black":"white");
}

bool AI::canBeChecked(const Board &b) {
 for (int i = 0; i<8; ++i) {
  for (int j = 0; j<8; ++j) {
   for (int x = 0; x<8; ++x) {
    for (int y = 0; y<8; ++y) {
     Board tempBoard(b);
     if(tempBoard.getBoard()[j][i] != nullptr &&
	tempBoard.getBoard()[j][i]->getColour() == team &&
	(tempBoard.moveTransform(i,j,x,y,'Q') || tempBoard.move(i,j,x,y)) && 
	tempBoard.checkCheck(team))
      return true;
    }
   }
  }
 }
 return false;
}

int AI::numValidMoves(const Board &b) {
 int n = 0;
 for (int i = 0; i<8; ++i) {
  for (int j = 0; j<8; ++j) {
   for (int x = 0; x<8; ++x) {
    for (int y = 0; y<8; ++y) {
     Board tempBoard(b);
     if(tempBoard.getBoard()[j][i] != nullptr &&
	tempBoard.getBoard()[j][i]->getColour() == team &&
	tempBoard.move(i,j,x,y))
      ++n;
    }
   }
  }
 }
 return n;
}

void AI::makeMove(Board *b) {
 srand(time(0));
 vector<Move> v;
 vector<Move> pref;
 int numMoves = 0, numMoves2 = 0;
 bool takeOrCheck = false;
 for (int i = 0; i<8; ++i) {
  for (int j = 0; j<8; ++j) {
   for (int x = 0; x<8; ++x) {
    for (int y = 0; y<8; ++y) {
//     cout << "trying " << i << j << " " << x << y;
     Board tempBoard{*b};
     tempBoard.changeTurns(team);
     if (tempBoard.getBoard()[j][i] != nullptr &&
         tempBoard.getBoard()[j][i]->getColour() == team &&
	 (tempBoard.moveTransform(i, j, x, y, 'Q') || tempBoard.move(i, j, x, y))) {
      Move m{i,j,x,y};
      if (level == 4) { //Highest level selected
	if (tempBoard.checkCheck(enemy) ||
           (b->getBoard()[y][x] != nullptr && b->getBoard()[y][x]->getColour() == enemy)) { //if a move can give check or capture an enemy piece
	 int n = numValidMoves(tempBoard);
	 if (n > numMoves || !takeOrCheck) { //add it to the pile of possible moves if it is equal or greater than other options in follow up moves
	  pref.resize(0);
	  pref.emplace_back(m);
	  numMoves = n;
	  takeOrCheck = true;
	 } else if (n == numMoves) {
	  pref.emplace_back(m);
	 }
	} else if (!canBeChecked(tempBoard) && !takeOrCheck) { //valued second to giving check or capturing is avoiding check
	 int n = numValidMoves(tempBoard);
	 if (n > numMoves) { //with a preference for an option with the most places to go from it.
          pref.resize(0);
          pref.emplace_back(m);
          numMoves = n;
         } else if (n == numMoves) {
          pref.emplace_back(m);
         }
	}
      } else if (level >= 2) { //if AI level is below 4 but not 1
       if (tempBoard.checkCheck(enemy) ||
          (b->getBoard()[y][x] != nullptr && b->getBoard()[y][x]->getColour() == enemy)) { //level two prefers giving check and capturing
	pref.emplace_back(m);
       }else if (level >= 3 && !canBeChecked(tempBoard)) { //level 3 also prefers avoiding checks
        pref.emplace_back(m);
       }
      }
      if (level == 4) {
        int n = numValidMoves(tempBoard);
	if (n > numMoves) {
         v.resize(0);
         v.emplace_back(m);
         numMoves = n;
        } else if (n == numMoves) {
         v.emplace_back(m);
        }
      } else {
      	v.emplace_back(m); //fill an array with every valid move
      }
     }
    }
   }
  }
 }
 cout << pref.size();
 b->changeTurns(team);
 if (pref.size()) {
  int ran = rand() % pref.size();
  if (!b->moveTransform(pref[ran].x1, pref[ran].y1, pref[ran].x2, pref[ran].y2, 'Q'))
   b->move(pref[ran].x1, pref[ran].y1, pref[ran].x2, pref[ran].y2);
 } else {
  int ran = rand() % v.size();
  if (!b->moveTransform(pref[ran].x1, pref[ran].y1, pref[ran].x2, pref[ran].y2, 'Q'))
   b->move(v[ran].x1, v[ran].y1, v[ran].x2, v[ran].y2);
 }
}

