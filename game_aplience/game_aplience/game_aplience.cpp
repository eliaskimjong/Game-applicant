#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

char square[10] = { '0', '1', '2', '3', '4', '5', '6','7', '8', '9' };
int stop = 0;
char mark = 'x';
char mark1 = 'o';
int input = 0;
int input2 = 0;
string playername1, playername2, guest;
int wins1 = 0;
int wins2 = 0;
double checks = 0;

// Class to handle Tic Tac Toe game logic and display
class TicTacToe {
public:
    // Function to check if there's a winner
    bool checkWin() {
        for (int i = 1; i <= 7; i += 3) {
            if (square[i] == square[i + 1] && square[i + 1] == square[i + 2]) {
                return true;
            }
        }

        for (int i = 1; i <= 3; ++i) {
            if (square[i] == square[i + 3] && square[i + 3] == square[i + 6]) {
                return true;
            }
        }

        if ((square[1] == square[5] && square[5] == square[9]) ||
            (square[3] == square[5] && square[5] == square[7])) {
            return true;
        }

        return false;
    }

    // Function to display the Tic Tac Toe board
    void displayBoard() {
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

    // Function to display player names and game results
    void displayData() {
        ofstream file("data/players.txt");
        cout << "Player 1: " << playername1 << " <X> vs Player 2: " << playername2 << " <O>" << endl;
        cout << wins1 << " vs " << wins2 << endl;
        file << "Player 1: " << playername1 << " <X> || Player 2: " << playername2 << " <O>" << endl;
        file << "Wins " << wins1 << " vs " << "Wins " << wins2 << endl;
    }

    // Function to get player names
    void getInput() {
        cout << "Enter Player 1 name: ";
        cin >> playername1;
        cout << "Enter Player 2 name: ";
        cin >> playername2;
        displayData();
    }

    // Function to reset the Tic Tac Toe board
    void resetBoard() {
        for (int i = 0; i < 10; ++i) {
            square[i] = '0' + i;
        }
    }
};

int main() {
    ofstream file;
    ifstream output;
    string ans, username, game;
    string account;
    map<string, string> DATA;
    DATA.insert(pair<string, string>(account, username));

    // User authentication loop
    while (!file.eof()) {
        cout << "Welcome to my app! Would you like to login or sign in?" << endl;
        cout << "(Answer with 'login' or 'create'): ";
        cin >> ans;

        if (ans == "login") {
            // Login process
            cout << "Username: ";
            cin >> username;
            output.open("data/database.txt");

            if (output.is_open()) {
                bool userFound = false;
                while (getline(output, guest)) {
                    if (username == guest) {
                        cout << "Login successful!" << endl;
                        userFound = true;
                        break;
                    }
                }

                if (!userFound) {
                    cout << "Sorry, but this username doesn't exist. Please try again." << endl;
                    cin >> username;
                    if (username == guest) {
                        cout << "Login successful!" << endl;
                    }
                }
            }
        }
        else if (ans == "create") {
            // Account creation process
            cout << "Username: ";
            cin >> guest;
            file.open("data/database.txt");
            file << DATA; //fix this later
            file << guest;
            username = guest;
            file.close();
        }
        else {
            cout << "Typed in wrong" << endl;
            continue;
        }

        // Game selection
        cout << "Hey " << username << "! Would you like to play tic tac toe or chess?" << endl;
        cout << "(Answer with '1' or '2')" << endl;
        cin >> game;

        if (game == "1") {
            while (game == "1") {
                TicTacToe ticTacToeGame;
                system("CLS");
                ticTacToeGame.getInput();
                ticTacToeGame.displayBoard();

                for (int x = 0; x < 11; x++) {
                    checks += 0.5;
                    cout << playername1 << " <X> choose a slot: ";
                    cin >> input;

                    // Handle input validation
                    if (input == input2) {
                        cout << "Tile is taken. Please enter a valid one ";
                        cin >> input;
                        square[input] = mark;
                    }
                    else {
                        square[input] = mark;
                    }

                    // Check for a winner
                    if (ticTacToeGame.checkWin()) {
                        ticTacToeGame.displayBoard();
                        cout << "Player " << playername1 << " wins!\n";
                        cout << "Would you like to save this game? ";
                        cin >> ans;

                        // Save game if requested
                        if (ans == "yes") {
                            int win = wins1 + 1;
                            ticTacToeGame.displayData();
                            file << playername2 << " won " << win << " times" << endl;
                        }

                        // Ask for replay
                        cout << "Would you like to replay? ";
                        cin >> ans;

                        if (ans == "yes") {
                            x = 0;
                            ticTacToeGame.resetBoard();
                            ticTacToeGame.displayBoard();
                            continue;
                        }
                        else {
                            break;
                        }
                    }

                    ticTacToeGame.displayBoard();
                    checks += 0.5;

                    // Check for a draw
                    if (checks == 5) {
                        cout << "Nobody won :(" << endl;
                        return 0;
                    }

                    cout << playername2 << " <O> choose a slot: ";
                    cin >> input2;

                    // Handle input validation
                    if (input2 == input) {
                        cout << "Tile is taken. Please enter a valid one ";
                        cin >> input2;
                        square[input2] = mark1;
                    }
                    else {
                        square[input2] = mark1;
                    }

                    system("CLS");
                    ticTacToeGame.displayBoard();

                    // Check for a winner
                    if (ticTacToeGame.checkWin()) {
                        ticTacToeGame.displayBoard();
                        cout << "Player " << playername2 << " wins!\n";

                        cout << "Would you like to save this game/win? ";
                        cin >> ans;

                        // Save game if requested
                        if (ans == "yes") {
                            int win = wins2 + 1;
                            ticTacToeGame.displayData();
                            file << playername2 << " won " << win << " times" << endl;
                        }

                        // Ask for replay
                        cout << "Would you like to replay? ";
                        cin >> ans;

                        if (ans == "yes") {
                            x = 0;
                            ticTacToeGame.resetBoard();
                            system("CLS");
                            ticTacToeGame.displayBoard();
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
            }
        }
        else {
            // Handle other games or options here
        }
        return 0;
    }
}
