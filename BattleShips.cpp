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
               fin >> current_x;
               fin >> current_y;
               fin >> direction;
               cout << "current x : " << current_x << "   current y : " << current_y << "   direction = " << direction << endl;
               if (!board_set_values(direction, current_x, current_y, i)) {
                   exit(1);
               }
           }
           display_board();
       }
    }

bool BattleShips::board_set_values(int& direction, int& x, int& y, int& i) {
    bool validFile = true;
    int runUpto = 0;
    string valueToPut;
    if (myarr[i] == "Carrier") {
        runUpto = 5;
        valueToPut = "c";
    } else if (myarr[i] == "BattleShip") {
        runUpto = 4;
        valueToPut = "b";
    } else if (myarr[i] == "Cruiser") {
        runUpto = 3;
        valueToPut = "r";
    } else if (myarr[i] == "Submarine") {
        runUpto = 3;
        valueToPut = "s";
    } else if (myarr[i] == "Destroyer") {
        runUpto = 2;
        valueToPut = "d";
    }

    if (direction == 0) {
        if (!check_if_occupied(direction, x, y, i)) {
            int temp = 0;
            for (int ii = 0; ii < runUpto; ii++) {
                board[x][y + temp] = valueToPut;
                temp++;
            }
            i++;
        } else {
            cout << "Fail! Ship Already Exists There! Try Again!\n";
            validFile = false;
        }
    } else if (direction == 1) {
        if (!check_if_occupied(direction, x, y, i)) {
            int temp = 0;
            for (int ii = 0; ii < runUpto; ii++) {
                board[x + temp][y] = valueToPut;
                temp++;
            }
            i++;
        } else {
            cout << "Fail! Ship Already Exists There! Try Again!\n";
            validFile = false;
        }
    }
return validFile;
}

bool BattleShips::check_if_occupied(int& direction, int& x, int& y, int& i) {
    bool isPresent = true;

    if (myarr[i] == "Carrier" && direction == 0) {
        if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-" && board[x][y + 3] == "-" &&
            board[x][y + 4] == "-") {
            isPresent = false;
        }

    } else if (myarr[i] == "Carrier" && direction == 1) {
        if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-" && board[x + 3][y] == "-" &&
            board[x + 4][y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[i] == "BattleShip" && direction == 0) {
        if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-" && board[x][y + 3] == "-") {
            isPresent = false;
        }

    } else if (myarr[i] == "BattleShip" && direction == 1) {
        if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-" && board[x + 3][y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[i] == "Cruiser" && direction == 0) {
        if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-") {
            isPresent = false;
        }

    } else if (myarr[i] == "Cruiser" && direction == 1) {
        if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[i] == "Submarine" && direction == 0) {
        if (board[x][y] == "-" && board[x][y + 1] == "-" && board[x][y + 2] == "-") {
            isPresent = false;
        }

    } else if (myarr[i] == "Submarine" && direction == 1) {
        if (board[x][y] == "-" && board[x + 1][y] == "-" && board[x + 2][y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[i] == "Destroyer" && direction == 0) {
        if (board[x][y] == "-" && board[x][y + 1] == "-") {
            isPresent = false;
        }

    } else if (myarr[i] == "Destroyer" && direction == 1) {
        if (board[x][y] == "-" && board[x + 1][y] == "-") {
            isPresent = false;
        }
    }


    return isPresent;
}
