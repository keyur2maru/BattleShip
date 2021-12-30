//
// Created by kd2ma on 12/28/2021.
//

#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "Input_Coordinates.h"
const int BOARD_DIMENSION = 10;
const int NUM_SHIPS = 5;
const std::string myarr[] = { "Carrier", "BattleShip", "Cruiser", "Submarine", "Destroyer" };

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::fstream;
using std::ifstream;
using std::istream;
using std::stringstream;

class Battle_Ships {
private:
    int player1_ships, player2_ships;
    vector<vector<string>> board;
    vector<vector<int>> missed_board;

public:
    void init_board();
    void init_board_manual();
    void display_board();

    bool board_set_values(struct Input_Coordinates& ic);
    bool check_if_occupied(struct Input_Coordinates& ic);
};
#endif // BATTLESHIP_H
