#include <iostream>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

 char square[10] = {'0', '1', '2', '3', '4', '5', '6','7', '8', '9'}; //board
 int stop = 0;
 char mark = 'x';  //player 1 mark
 char mark1 = 'o'; //player 2 mark
 int input = 0; //input from player 1
 int input2 = 0; //input from player 2
 string playername1, playername2, login; 
 int wins1 = 0;
 int wins2 = 0; 
 double checks = 0;
class tictactoe{


public:
    bool checkWin() { //checking for wins with bool
        // Check rows
        for (int i = 1; i <= 7; i += 3) {
            if (square[i] == square[i + 1] && square[i + 1] == square[i + 2]) {
                return true;
            }
        }

        // Check columns
        for (int i = 1; i <= 3; ++i) {
            if (square[i] == square[i + 3] && square[i + 3] == square[i + 6]) {
                return true;
            }
        }

        // Check diagonals
        if ((square[1] == square[5] && square[5] == square[9]) ||
            (square[3] == square[5] && square[5] == square[7])) {
            return true;
        }

        return false;
    }

    void board() { //this fixes the lines between each tile
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
    void data(){ //for printing out player name and saving it in file
        ofstream file;
        file.open("data/players.txt");
        cout << "player name 1: " << playername1 << " <X>" << " vs player name 2: " << playername2 << " <O>" << endl; //
        cout << wins1 << " vs " << wins2 << endl;   
        file << "player name 1: " << playername1 << " <X>" << " || player name 2: " << playername2 << " <0>" << endl;
        file << "wins " << wins1 << " vs " << "wins" << wins2 << endl;
    }
    void getinput(){ //for getting user input
        cout << "enter player 1 name: ";
        cin >> playername1;
        cout << "enter player 2 name: ";
        cin >> playername2;
        data();
    }
    void resetBoard(char square[]) {//resets the board
        for (int i = 0; i < 10; ++i) {
            square[i] = '0' + i; //after every loop it adds 1 to square[i]
        }
    }
};

int main() {
    ofstream file;//for storing data
    ifstream output; //for outputting data
    string ans, username, game; 
    while (!file.eof()) {
        cout << "Welcome to my app! Would you like to login or sign in?" << endl;
        cout << "(answer with login or create): ";
        cin >> ans;
        if (ans == "login") {
            cout << "Username: ";
            cin >> username;
            output.open("data/database.txt");
            if (output.is_open()) {
                while (getline(output, login)) {
                if (username == login) {
                    cout << "Login successful!" << endl;
                }
                else {
                    cout << "Sorry, but this username doesn't exist. Please try again." << endl;
                    cin >> username;
                    if (username == login) {
                        cout << "Login successful!" << endl;
                    }
                }

                }
                
            }
        }
        else if (ans == "create") {

            cout << "Username: ";
            cin >> login;  // Store the username in the login variable
            file.open("data/database.txt");
            file << login;
            username = login;
            file.close();
        }
        else {
            cout << "typed in wrong" << endl;
            continue;
        }
        cout << "Hey " << username << "! Would like to play tic tac toe or chess?" << endl; //this is the first part of program
        cout << "(answer with 1 or 2)" << endl;
        cin >> game;
        if (game == "yes") { //For tic tac toe game
            while (game == "yes") {
            tictactoe ticTacToeGame;
            system("CLS");
            ticTacToeGame.getinput();
            ticTacToeGame.board();
            for (int x = 0; x < 11; x++) { 
                checks += 0.5;
                cout << playername1 << " <X> vilken slot: " << checks;
                cin >> input;
                if (input == input2) {
                    cout << "Tile is taken. Please enter a valid one ";
                    cin >> input;
                    square[input] = mark;
                }
                else {
                    square[input] = mark; 
                }
                if (ticTacToeGame.checkWin()) {
                    ticTacToeGame.board();
                    cout << "Player " << playername1 << " wins!\n";
                    cout << "would u like to save this game?";
                    cin >> ans;
                    if (ans == "yes") {
                        int win = wins1 + 1;
                        ticTacToeGame.data();
                        file << playername2 << " won " << win << " times" << endl;
                    }
                    cout << "would you like to replay? ";
                    cin >> ans;
                    if (ans == "yes") { 
                        x = 0;
                        ticTacToeGame.resetBoard(square);
                        ticTacToeGame.board();
                        continue;
                        
                    }
                    else {
                        break;
                    }
                }
                ticTacToeGame.board();
                checks += 0.5;
                if (checks == 5) {
                    cout << "nobody won :(" << endl;
                    return 0;
                }
                cout << playername2 << " <O> vilken slot: " << checks ;
                cin >> input2;
                if (input2 == input) {
                    cout << "Tile is taken. Please enter a valid one ";
                    cin >> input2;
                    square[input2] = mark1;
                }
                else {
                    square[input2] = mark1;
                }
                system("CLS");
                ticTacToeGame.board();
                if (ticTacToeGame.checkWin()) {
                    ticTacToeGame.board();
                    cout << "Player " << playername2 << " wins!\n";
                    
                    cout << "would you like to save this game/win?";
                    cin >> ans;
                    if (ans == "yes") {
                        int win = wins2 + 1;
                        ticTacToeGame.data();
                        file << playername2 << " won " << win << " times" << endl;
                    }
                    cout << "would you like to replay? ";
                    cin >> ans;
                    if(ans == "yes") {
                        x = 0;
                        ticTacToeGame.resetBoard(square);
                        system("CLS");
                        ticTacToeGame.board();
                        continue;
                    }
                    else {
                      break;
                    } 
                }
            }
            }
        }
        else
        {

        }
        return 0;
    }
}