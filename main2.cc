#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// forward declaratations
void draw_board(const vector<char>* board);
void get_input(const vector<char>& board, int* choice, int player);
bool ok_input(const vector<char>& board, int* choice);
void update_board(vector<char>& board, int input, int player);
char check_game_state(const vector<char>& board, int turn);
bool check_columns(const vector<char>& board, char c);
bool check_rows(const vector<char>& board, char c);
bool check_diagonal(const vector<char>& board, char c);

int main(int argc, char* argv[]) {
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int cur_player  = 1;
    int turn_number = 1;
    int input;

    cout << "Welcome to TIC-TAC-TOE" << endl;
    // create the pieces
    // do the turn
    // get input
    // update the board
    // check for win

    draw_board(&board);

    while (true) {
        get_input(board, &input, cur_player);
        update_board(board, input, cur_player);
        draw_board(&board);
        char state = check_game_state(board, turn_number);

        switch (state) {
            case 'X':
                cout << "Player 1 Won!" << endl;
                return 0;
            case 'O':
                cout << "Player 2 Won!" << endl;
                return 0;
            case 'D':
                cout << "Draw!" << endl;
                return 0;
            default:
                break;
        }
        turn_number++;
        cur_player = (cur_player % 2) + 1;
    }

    return 0;
}

void draw_board(const vector<char>* board) {
    int index = 1;

    cout << "-------------------" << endl;
    for (char c : *board) {
        cout << "|  " << c << "  ";
        if (index % 3 == 0) {
            cout << "|" << endl;
            cout << "-------------------" << endl;
        }
        index++;
    }
    cout << endl;
}

void get_input(const vector<char>& board, int* choice, int player) {
    string line;
    cout << "Player " << player << " please enter an open tile between 1-9" << endl;

    while (true) {
        if (!getline(cin, line)) {
            return;
        }

        stringstream ss(line);
        if ((ss >> *choice) && (ss.rdbuf()->in_avail() == 0)) {
            if (ok_input(board, &(*choice))) {
                break;
            }
        }
        cout << "Invalid input. Please enter a single, open number between 1-9." << endl;
    }
}

bool ok_input(const vector<char>& board, int* choice) {
    int c = *choice;
    if (c > 9 || c < 1) {
        cerr << "ERROR: CHOICE MUST BE A NUMBER BETWEEN 1-9" << endl;
        return false;
    } else if (board[c - 1] == 'X' || board[c - 1] == 'O') {
        cerr << "ERROR: POSITION AT CHOICE " << c << " MUST BE OPEN" << endl;
        return false;
    }
    return true;
}

void update_board(vector<char>& board, int input, int player) {
    player == 1 ? board[input - 1] = 'X' : board[input - 1] = 'O';
}

char check_game_state(const vector<char>& board, int turn) {
    if (check_rows(board, 'X') || check_columns(board, 'X') || check_diagonal(board, 'X')) {
        return 'X';
    }
    if (check_rows(board, 'O') || check_columns(board, 'O') || check_diagonal(board, 'O')) {
        return 'O';
    }
    if (turn == 9) {
        return 'D';
    }
    return 'C';
}

bool check_rows(const vector<char>& board, char c) {
    if (board[0] == c && board[1] == c && board[2] == c) {
        return true;
    }
    if (board[3] == c && board[4] == c && board[5] == c) {
        return true;
    }
    if (board[6] == c && board[7] == c && board[8] == c) {
        return true;
    }
    return false;
}

bool check_columns(const vector<char>& board, char c) {
    int x = 0, y = 0, z = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == c) {
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

bool check_diagonal(const vector<char>& board, char c) {
    if (board[0] == c && board[4] == c && board[8] == c) {
        return true;
    }
    if (board[2] == c && board[4] == c && board[6] == c) {
        return true;
    }
    return false;
}
