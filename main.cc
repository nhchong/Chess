#include "controller.h"
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
    Controller *controller = new Controller();
    Board b;
    bool boardFromSetup = false;
    if (argc == 2) {
        boardFromSetup = true;
        b = controller->Import(b, argv[1]);
        cout << "Your imported board is the following..." << endl;
        b.printBoard();
    }
    cout << "Welcome to Chess. Please enter a command (game/setup/resign)." << endl;
    string command;
    float whiteWins = 0;
    float blackWins = 0;
    while (cin >> command) {
        if (command == "game" ) { // begin game play
            controller->inGame = true;
            string winner;
            if (boardFromSetup) {
              winner = controller->play(b);
            } else {
              Board c;
              winner = controller->play(c);
            }
            if (winner == "white") ++whiteWins;
            if (winner == "black") ++blackWins;
            if (winner == "tie") {
                whiteWins += 0.5;
                blackWins += 0.5;
            }
       } else if (command == "setup") { // enter setup mode
            if (controller->inGame == true) {
                cout << "Cannot enter setup mode when game is in progress" << endl;
            } else {
                boardFromSetup = true;
                b = controller->setup(b);
            }
        } else if (command == "resign") {        // command entered was "resign"
                controller->quit = true;
        } else {
		cout << "Invalid command, options are: game, setup, and resign" <<endl;
	}
    }
    cout << "Final Score:" << endl;
    cout << "White: " << whiteWins << endl;
    cout << "Black: " << blackWins << endl;
}

