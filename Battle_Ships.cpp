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

void Battle_Ships::init_fleet() {
    string input;
    cout << "Deploy Player Ships: \nSelect input configuration (file/manual/random): ";
    cin >> input;
    if (input == "manual") {
        init_fleet_manual();
    } else if (input == "file") {
        init_fleet_file();
    } else if (input == "random") {
        init_fleet_randomize();
    }
}

bool Battle_Ships::board_set_values(struct Input_Coordinates& ic) {
    bool validFile = true;
    int runUpto = 0;
    string valueToPut;

    get_run_upto(runUpto, valueToPut, ic);

    if (ic.direction == 0) {
        if (!check_if_occupied(ic)) {
            int temp = 0;
            for (int ii = 0; ii < runUpto; ii++) {
                board[ic.x][ic.y + temp] = valueToPut;
                temp++;
            }
        } else {
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
            validFile = false;
        }
    }
return validFile;
}

bool Battle_Ships::check_if_occupied(struct Input_Coordinates& ic) {
    bool isPresent = false;
    int runUpto = 0;
    string placeholder;
    get_run_upto(runUpto, placeholder, ic);

    if (ic.direction == 0) {
        int ii = 0;
        while (ii < runUpto) {
            if (board[ic.x][ic.y + ii] != "-") {
                isPresent = true;
            }
            ii++;
        }
    } else if (ic.direction == 1) {
        int ii = 0;
        while (ii < runUpto) {
            if (board[ic.x + ii][ic.y] != "-") {
                isPresent = true;
            }
            ii++;
        }
    }
    return isPresent;
}

void Battle_Ships::reset_board() {
for (auto & i : board) {
    for (int j = 0; j < board.size(); j++) {
        i[j] = "-";
    }
}
}

void Battle_Ships::isMoveValid(int &tempmax_x, int &tempmax_y, struct Input_Coordinates &ic) {
    for (int i = ic.whichShip; i < ic.whichShip + 1; i++) {
        switch (i) {
            case 0:
                tempmax_x = 9;
                tempmax_y = 5;
                break;
            case 1:
                tempmax_x = 9;
                tempmax_y = 6;
                break;
            case 2:
            case 3:
                tempmax_x = 9;
                tempmax_y = 7;
                break;
            case 4:
                tempmax_x = 9;
                tempmax_y = 8;
                break;
            default:
                cout << "WRONG";
                exit(1);
        }

    }
}

int Battle_Ships::getRandom(int min, int max) {
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    std::uniform_int_distribution<> dist(min, max); // create distribution for integers with [1; 9] range
    auto random_number = dist(engine);
    return random_number;
}

bool Battle_Ships::init_fleet_manual() {
    int inputCounter = 0;
    Input_Coordinates ic;
    while (inputCounter < NUM_SHIPS) {
        printf("Enter Direction: 0 for Horizontal, 1 for Vertical for %s:", myarr[inputCounter].c_str());
        cin >> ic.direction;
        printf("\nEnter x coordinates for %s:", myarr[inputCounter].c_str());
        cin >> ic.x;
        printf("\nEnter y coordinates for %s:", myarr[inputCounter].c_str());
        cin >> ic.y;
        ic.whichShip = inputCounter;
        int max_x = 0;
        int max_y = 0;
        isMoveValid(max_x, max_y, ic);

        if ((ic.x <= max_x && ic.y <= max_y && ic.direction == 0) || (ic.x <= max_y && ic.y <= max_x && ic.direction == 1)) {
            if (board_set_values(ic)) {
                inputCounter++;
            }
        }
        else {
            if (ic.direction == 0) {
                cout << "Error! Out of Range!\nMaximum value for X coordinate = " << max_x << " Maximum value for Y coordinate = " << max_y << "\n";
            }
            else if (ic.direction == 1) {
                cout << "Error! Out of Range!\nMaximum value for X coordinate = " << max_y << " Maximum value for Y coordinate = " << max_x << "\n";
            }
        }
    }
    return true;
}

bool Battle_Ships::init_fleet_randomize() {
    Input_Coordinates ic;
    int inputCounter = 0;
    while (inputCounter < NUM_SHIPS) {
        ic.whichShip = inputCounter;
        int tempmax_x = 0;
        int tempmax_y = 0;
        ic.direction = getRandom(0, 1);
        isMoveValid(tempmax_x, tempmax_y, ic);
        if (ic.direction == 0) {
            int random_number = getRandom(0,tempmax_x);
            ic.x = random_number;
            random_number = getRandom(0,tempmax_y);
            ic.y = random_number;

        } else if (ic.direction == 1) {
            int random_number = getRandom(0,tempmax_y);
            ic.x = random_number;
            random_number = getRandom(0,tempmax_x);
            ic.y = random_number;
        }

        if (board_set_values(ic)) {
            inputCounter++;
        }
    }
    return true;
}

bool Battle_Ships::init_fleet_file() {
    Input_Coordinates ic;
    ifstream fin;
    string fName;
    int inputCounter = 0;
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
        int max_x = 0;
        int max_y = 0;
        isMoveValid(max_x, max_y, ic);
        if ((ic.x <= max_x && ic.y <= max_y && ic.direction == 0) || (ic.x <= max_y && ic.y <= max_x && ic.direction == 1))  {
            if(board_set_values(ic)) {
                inputCounter++;
            }
            else {
                which_ship_present(ic);
                cout << "Ship Already Exists At : " << ic.x << " " << ic.y << "\n";
                exit(1);
            }
        }
        else {
            cout << "Check input coordinates for " << fName << "\n";
            cout << "Error at Input Coordinates: x = " << ic.x << " y = " << ic.y << " direction = " << ic.direction << "\n";
            if (ic.x > max_x && ic.direction == 0) {
                cout << "Max X coordinate: " << max_x << "\n";
            }
            if (ic.y > max_y && ic.direction == 0) {
                cout << "Max Y coordinate: " << max_y << "\n";
            }
            if (ic.x > max_y && ic.direction == 1) {
                cout << "Max X coordinate: " << max_y << "\n";
            }
            if (ic.y > max_x && ic.direction == 1) {
                cout << "Max Y coordinate: " << max_x << "\n";
            }
            exit(1);
        }
    }
    return true;
}

void Battle_Ships::get_run_upto(int& runUpto, string& value, struct Input_Coordinates& ic) {
    if (myarr[ic.whichShip] == "Carrier") {
        runUpto = 5;
        value = "c";
    } else if (myarr[ic.whichShip] == "BattleShip") {
        runUpto = 4;
        value = "b";
    } else if (myarr[ic.whichShip] == "Cruiser") {
        runUpto = 3;
        value = "r";
    } else if (myarr[ic.whichShip] == "Submarine") {
        runUpto = 3;
        value = "s";
    } else if (myarr[ic.whichShip] == "Destroyer") {
        runUpto = 2;
        value = "d";
    }
}


void Battle_Ships::which_ship_present(struct Input_Coordinates& ic) {
    int runUpto = 0;
    string ship_name;
    get_run_upto(runUpto, ship_name, ic);
    int i = 0;
    while (i < runUpto) {
        if (ic.direction == 0) {
            if (board[ic.x][ic.y + i] != "-") {
                ship_name = board[ic.x][ic.y + i];
            }
        } else if (ic.direction == 1) {
            if (board[ic.x + i][ic.y] != "-") {
                ship_name = board[ic.x][ic.y + i];
            }
        }
        if (ship_name == "c") {
            ship_name = myarr[0];
        }
        else if (ship_name == "b") {
            ship_name = myarr[1];
        }
        else if (ship_name == "r") {
            ship_name = myarr[2];
        }
        else if (ship_name == "s") {
            ship_name = myarr[3];
        }
        else if (ship_name == "d") {
            ship_name = myarr[4];
        }
        i++;
    }
    cout << "Ship present: " << ship_name <<  "\n";
    }





