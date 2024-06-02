#include <iostream>
#include <list>
using namespace std;


class Player {
protected:
    char mark;
public:
    virtual void setMark(char m) = 0;
    virtual char getMark() const = 0;
   
};


class TicTacToePlayer : public Player {
public:
    void setMark(char m) override {
        mark = m;
    }
    char getMark() const override {
        return mark;
    }
};

// Class representing the Tic Tac Toe board and game logic
class TicTacToeGame {
private:
    char square[10];    
    Player* player1;
    Player* player2;
    int currentPlayer;
    list<int> moves;  // List to store moves

public:
    TicTacToeGame() {
        for (int i = 0; i < 10; i++) {
            square[i] = '0' + i;
        }
        player1 = new TicTacToePlayer();
        player2 = new TicTacToePlayer();
        player1->setMark('X');
        player2->setMark('O');
        currentPlayer = 1;
    }

    ~TicTacToeGame() {
        delete player1;
        delete player2;
    }

    void displayBoard() const {
        cout << "     |     |     " << endl;
        cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;
        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;
        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;
        cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;
        cout << "     |     |     " << endl << endl;
    }

    void play() {
        int status;
        int choice;
        do {
            displayBoard();
            Player* currentPlayerRef = (currentPlayer == 1) ? player1 : player2;
            cout << "Player " << currentPlayer << " (" << currentPlayerRef->getMark() << "), enter a number:  ";
            cin >> choice;

            if (makeMove(choice, currentPlayerRef->getMark())) {
                moves.push_back(choice);  // Add move to list
                status = checkWin();
                currentPlayer = (currentPlayer % 2) ? 2 : 1;
            } else {
                cout << "Invalid move ";
               
            }
        } while (status == -1);

        displayBoard();
        if (status == 1) {
            currentPlayer = (currentPlayer % 2) ? 2 : 1;
            cout << "==>\aPlayer " << currentPlayer << " wins "<<endl;
        } else {
            cout << "==>\aGame draw"<<endl;
        }

        displayMoves();
    }

private:
    bool makeMove(int choice, char mark) {
        if (choice >= 1 && choice <= 9 && square[choice] == ('0' + choice)) {
            square[choice] = mark;
            return true;
        }
        return false;
    }

    int checkWin() const {
        if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' 
             && square[4] != '4' && square[5] != '5' && square[6] != '6' 
             && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

    void displayMoves() const {
        cout << "Moves made: ";
        for (int move : moves) {
            cout << move << " ";
        }
        cout << endl;
    }
};

int main() {
    TicTacToeGame game;
    game.play();
    return 0;
}
