//
// Created by kd2ma on 12/28/2021.
//

#include "BattleShips.h"
void BattleShips::init_board() {
for (int i = 0; i < BOARD_DIMENSION; i++) {
    vector<string> temp;
    temp.reserve(BOARD_DIMENSION);
for (int j = 0; j < BOARD_DIMENSION; j++) {
        temp.emplace_back("-");
    }
    board.push_back(temp);
}
}

void BattleShips::display_board()
{
    cout << "  ";
    for (int i = 0; i < BOARD_DIMENSION; i++)
    {
        cout << i << "  ";
    }
    cout << "\n";
for (int i = 0; i < BOARD_DIMENSION; i++) {
    cout << i << " ";
    for (int j = 0; j < BOARD_DIMENSION; j++) {
        cout << board[i][j] << "  ";
    }
    cout << endl;
}
}

void BattleShips::init_board_manual() {
    int input;
    cout << "Deploy Player Ships: \nEnter 0 for File Placement or Enter 1 for Manual Placement:";
    cin >> input;
    int i = 0;
    if (input == 1) {
        while (i < NUM_SHIPS) {
            int direction;
            int x, y;
            printf("Enter Direction: 0 for Horizontal, 1 for Vertical for %s:", myarr[i].c_str());
            cin >> direction;
            printf("\nEnter x coordinates for %s:", myarr[i].c_str());
            cin >> x;
            printf("\nEnter y coordinates for %s:", myarr[i].c_str());
            cin >> y;
            board_set_values(direction, x, y, i);
        }
    } else if (input == 0) {
        ifstream fin;
        string fName;
        int current_x;
        int current_y;
        int direction;
        cout << "Enter file name to initialize the fleet:\n";
        cin >> fName;
        cout << fName << endl;
        fin.open(fName);
        if (fin.fail()) {
            cout << "Couldn't read the file!\n";
        }
       while (fin >> fName) {
           if(fName == "carrier") {
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               if (direction == current_x) {
                   direction = 1;
               }
               else  {
                   fin >> direction;
                   if (direction == current_y) {
                       direction = 0;
                   }
               }
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (board_set_values(direction, current_x, current_y, i) == false) {
                   exit(1);
               }
           }
           if(fName == "battleship") {
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               if (direction == current_x) {
                   direction = 1;
               }
               else  {
                   fin >> direction;
                   if (direction == current_y) {
                       direction = 0;
                   }
               }
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (board_set_values(direction, current_x, current_y, i) == false) {
                   exit(1);
               }
           }

           if(fName == "cruiser") {
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               if (direction == current_x) {
                   direction = 1;
               }
               else  {
                   fin >> direction;
                   if (direction == current_y) {
                       direction = 0;
                   }
               }
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (board_set_values(direction, current_x, current_y, i) == false) {
                   exit(1);
               }
           }
           if(fName == "submarine") {
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               if (direction == current_x) {
                   direction = 1;
               }
               else  {
                   fin >> direction;
                   if (direction == current_y) {
                       direction = 0;
                   }
               }
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (board_set_values(direction, current_x, current_y, i) == false) {
                   exit(1);
               }
           }
           if(fName == "destroyer") {
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               if (direction == current_x) {
                   direction = 1;
               }
               else  {
                   fin >> direction;
                   if (direction == current_y) {
                       direction = 0;
                   }
               }
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (board_set_values(direction, current_x, current_y, i) == false) {
                   exit(1);
               }
           }
       }
    }
}

bool BattleShips::board_set_values(int& direction, int& x, int& y, int& i) {
    bool validFile = true;
    if (myarr[i] == "Carrier") {
        if (direction == 0) {
            if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-" && board[x][y + 3] == "-" &&
                board[x][y + 4] == "-") {
                board[x][y] = "c";
                board[x][y + 1] = "c";
                board[x][y + 2] = "c";
                board[x][y + 3] = "c";
                board[x][y + 4] = "c";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        } else if (direction == 1) {
            if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-" && board[x + 3][y] == "-" &&
                board[x + 4][y] == "-") {
                board[x][y] = "c";
                board[x + 1][y] = "c";
                board[x + 2][y] = "c";
                board[x + 3][y] = "c";
                board[x + 4][y] = "c";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        }
    } else if (myarr[i] == "BattleShip") {
        if (direction == 0) {
            if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-" && board[x][y + 3] == "-") {
                board[x][y] = "b";
                board[x][y + 1] = "b";
                board[x][y + 2] = "b";
                board[x][y + 3] = "b";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
            }
        } else if (direction == 1) {
            if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-" && board[x + 3][y] == "-") {
                board[x][y] = "b";
                board[x + 1][y] = "b";
                board[x + 2][y] = "b";
                board[x + 3][y] = "b";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        }
    } else if (myarr[i] == "Cruiser") {
        if (direction == 0) {
            if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-") {
                board[x][y] = "r";
                board[x][y + 1] = "r";
                board[x][y + 2] = "r";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        } else if (direction == 1) {
            if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-") {
                board[x][y] = "r";
                board[x + 1][y] = "r";
                board[x + 2][y] = "r";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        }

    } else if (myarr[i] == "Submarine") {
        if (direction == 0) {
            if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-") {
                board[x][y] = "s";
                board[x][y + 1] = "s";
                board[x][y + 2] = "s";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        } else if (direction == 1) {
            if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-") {
                board[x][y] = "s";
                board[x + 1][y] = "s";
                board[x + 2][y] = "s";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        }

    } else if (myarr[i] == "Destroyer") {
        if (direction == 0) {
            if (board[x][y] == "-" && board[x][y + 1] == "-") {
                board[x][y] = "d";
                board[x][y + 1] = "d";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        } else if (direction == 1) {
            if (board[x][y] == "-" && board[x + 1][y] == "-") {
                board[x][y] = "d";
                board[x + 1][y] = "d";
                i++;
            }
            else {
                cout << "Fail! Ship Already Exists There! Try Again!\n";
                validFile = false;
            }
        }
    }
    return validFile;
}