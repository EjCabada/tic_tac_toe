#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void draw_board(const vector<char>& board) {
    int index = 1;

    cout << "-------------------" << endl;
    for (char c : board) {
        cout << "|  " << c << "  ";
        if (index % 3 == 0) {
            cout << "|" << endl;
            cout << "-------------------" << endl;
        }
        index++;
    }
}

bool checkrows(vector<char>& b, char c) {
    if (b[0] == c && b[1] == c && b[2] == c) {
        return true;
    }
    if (b[3] == c && b[4] == c && b[5] == c) {
        return true;
    }
    if (b[6] == c && b[7] == c && b[8] == c) {
        return true;
    }
    return false;
}

bool checkColumns(vector<char>& b, char c) {
    int x = 0, y = 0, z = 0;
    for (int i = 0; i < 9; i++) {
        if (b[i] == c) {
            if (i % 3 == 0)
                x++;
            if (i % 3 == 1)
                y++;
            if (i % 3 == 2)
                z++;
        }
    }
    if (x == 3 || y == 3 || z == 3) {
        return true;
    }
    return false;
}

char checkGameState(vector<char>& b, int turn) {
    if (checkrows(b, 'X') || checkColumns(b, 'X')) {
        // cout << "Game Over: Player 1 won!!!" << endl;
        return 'X';
    }
    if (checkrows(b, 'O') || checkColumns(b, 'O')) {
        // cout << "Game Over: Plater 2 won!!!" << endl;
        return 'O';
    }
    if (turn == 8) {
        // cout << "GAME ENDED: DRAW";
        return 'D';
    }
    return 'C';
}

bool update_board(vector<char>& board, int choice, int player) {
    if (choice > 10 || choice < 1) {
        cerr << "Error Choice must be between 1 to 9, please try again" << endl;
        return false;
    } else if (board[choice - 1] == 'X' || board[choice - 1] == 'O') {
        cerr << "Error Choice must be open" << endl;
        return false;
    } else {
        player == 1 ? board[choice - 1] = 'X' : board[choice - 1] = 'O';
        return true;
    }
}

void getInput(int* choice) {
    string input;
    if (getline(cin, input)) {
        stringstream ss(input);
        if (ss >> *choice) {
            char remaining;
            if (ss >> remaining) {
                cout << "ERROR: must be a single int" << endl;
                cin.clear();
                cin.ignore();
                getInput(choice);
                return;
            }
        }
    }
}

void p_move(vector<char>& board, int* turn) {
    int player = (*turn % 2) + 1;
    int choice;

    cout << "PLAYER " << player << " TURN:\n";
    draw_board(board);
    cout << "Please chose num of spot you want to mark" << endl;
    getInput(&choice);

    if (update_board(board, choice, player)) {
        // cout << "update succesful" << endl;
        (*turn)++;
        return;
    } else {
        p_move(board, &(*turn));
    }
}

int main(int argc, char* argv[]) {
    int          turn  = 0;
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    cout << "WELCOME TO TIC-TAC-TOE" << endl;

    while (true) {
        // cout << "p_move entering" << endl;
        p_move(board, &turn);

        char state = checkGameState(board, turn);
        switch (state) {
            case 'X':
                cout << "Player 1 Won!" << endl;
                break;
            case 'O':
                cout << "Player 2 Won!" << endl;
                break;
            case 'D':
                cout << "Draw!" << endl;
                break;
            defualt:
                break;
        }
        if (state != 'C') {
            draw_board(board);
            break;
        }
        cout << endl;
    }

    return 0;
}
