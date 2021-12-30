//
// Created by kd2ma on 12/28/2021.
//

#include "Battle_Ships.h"
void Battle_Ships::init_board() {
for (int i = 0; i < BOARD_DIMENSION; i++) {
    vector<string> temp;
    temp.reserve(BOARD_DIMENSION);
for (int j = 0; j < BOARD_DIMENSION; j++) {
        temp.emplace_back("-");
    }
    board.emplace_back(temp);
}
}

void Battle_Ships::display_board()
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

void Battle_Ships::init_board_manual() {
    Input_Coordinates ic;
    int input;
    cout << "Deploy Player Ships: \nEnter 0 for File Placement or Enter 1 for Manual Placement:";
    cin >> input;
    int inputCounter = 0;
    if (input == 1) {
        while (inputCounter < NUM_SHIPS) {
            printf("Enter Direction: 0 for Horizontal, 1 for Vertical for %s:", myarr[inputCounter].c_str());
            cin >> ic.direction;
            printf("\nEnter x coordinates for %s:", myarr[inputCounter].c_str());
            cin >> ic.x;
            printf("\nEnter y coordinates for %s:", myarr[inputCounter].c_str());
            cin >> ic.y;
            ic.whichShip = inputCounter;

            if(board_set_values(ic)) {
             inputCounter++;
            }
        }
    } else if (input == 0) {
        ifstream fin;
        string fName;
        cout << "Enter file name to initialize the fleet:\n";
        cin >> fName;
        cout << fName << endl;
        fin.open(fName);
        if (fin.fail()) {
            cout << "Couldn't read the file!\n";
        }
       while (fin >> fName) {
               fin >> ic.x;
               fin >> ic.y;
               fin >> ic.direction;
               ic.whichShip = inputCounter;
               cout << "current x : " << ic.x << "   current y : " << ic.y << "   direction = " << ic.direction << endl;

               if (!board_set_values(ic)) {
                   exit(1);
               }
               else {
                   inputCounter++;
               }
        }
       }
    }

bool Battle_Ships::board_set_values(struct Input_Coordinates& ic) {
    bool validFile = true;
    int runUpto = 0;
    string valueToPut;
    if (myarr[ic.whichShip] == "Carrier") {
        runUpto = 5;
        valueToPut = "c";
    } else if (myarr[ic.whichShip] == "BattleShip") {
        runUpto = 4;
        valueToPut = "b";
    } else if (myarr[ic.whichShip] == "Cruiser") {
        runUpto = 3;
        valueToPut = "r";
    } else if (myarr[ic.whichShip] == "Submarine") {
        runUpto = 3;
        valueToPut = "s";
    } else if (myarr[ic.whichShip] == "Destroyer") {
        runUpto = 2;
        valueToPut = "d";
    }

    if (ic.direction == 0) {
        if (!check_if_occupied(ic)) {
            int temp = 0;
            for (int ii = 0; ii < runUpto; ii++) {
                board[ic.x][ic.y + temp] = valueToPut;
                temp++;
            }
        } else {
            cout << "Fail! Ship Already Exists There! Try Again!\n";
            validFile = false;
        }
    } else if (ic.direction == 1) {
        if (!check_if_occupied(ic)) {
            int temp = 0;
            for (int ii = 0; ii < runUpto; ii++) {
                board[ic.x + temp][ic.y] = valueToPut;
                temp++;
            }
        } else {
            cout << "Fail! Ship Already Exists There! Try Again!\n";
            validFile = false;
        }
    }
return validFile;
}

bool Battle_Ships::check_if_occupied(struct Input_Coordinates& ic) {
    bool isPresent = true;

    if (myarr[ic.whichShip] == "Carrier" && ic.direction == 0) {
        if (board[ic.x][ic.y] == "-" && board[ic.x][ic.y + 1] == "-" && board[ic.x][ic.y + 2] == "-" && board[ic.x][ic.y + 3] == "-" &&
            board[ic.x][ic.y + 4] == "-") {
            isPresent = false;
        }

    } else if (myarr[ic.whichShip] == "Carrier" && ic.direction == 1) {
        if (board[ic.x][ic.y] == "-" && board[ic.x + 1][ic.y] == "-" && board[ic.x + 2][ic.y] == "-" && board[ic.x + 3][ic.y] == "-" &&
            board[ic.x + 4][ic.y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[ic.whichShip] == "BattleShip" && ic.direction == 0) {
        if (board[ic.x][ic.y] == "-" && board[ic.x][ic.y + 1] == "-" && board[ic.x][ic.y + 2] == "-" && board[ic.x][ic.y + 3] == "-") {
            isPresent = false;
        }

    } else if (myarr[ic.whichShip] == "BattleShip" && ic.direction == 1) {
        if (board[ic.x][ic.y] == "-" && board[ic.x + 1][ic.y] == "-" && board[ic.x + 2][ic.y] == "-" && board[ic.x + 3][ic.y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[ic.whichShip] == "Cruiser" && ic.direction == 0) {
        if (board[ic.x][ic.y] == "-" && board[ic.x][ic.y + 1] == "-" && board[ic.x][ic.y + 2] == "-") {
            isPresent = false;
        }

    } else if (myarr[ic.whichShip] == "Cruiser" && ic.direction == 1) {
        if (board[ic.x][ic.y] == "-" && board[ic.x + 1][ic.y] == "-" && board[ic.x + 2][ic.y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[ic.whichShip] == "Submarine" && ic.direction == 0) {
        if (board[ic.x][ic.y] == "-" && board[ic.x][ic.y + 1] == "-" && board[ic.x][ic.y + 2] == "-") {
            isPresent = false;
        }

    } else if (myarr[ic.whichShip] == "Submarine" && ic.direction == 1) {
        if (board[ic.x][ic.y] == "-" && board[ic.x + 1][ic.y] == "-" && board[ic.x + 2][ic.y] == "-") {
            isPresent = false;
        }
    }

    if (myarr[ic.whichShip] == "Destroyer" && ic.direction == 0) {
        if (board[ic.x][ic.y] == "-" && board[ic.x][ic.y + 1] == "-") {
            isPresent = false;
        }

    } else if (myarr[ic.whichShip] == "Destroyer" && ic.direction == 1) {
        if (board[ic.x][ic.y] == "-" && board[ic.x + 1][ic.y] == "-") {
            isPresent = false;
        }
    }


    return isPresent;
}
