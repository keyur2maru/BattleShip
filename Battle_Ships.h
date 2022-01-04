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
#include <ctime>
#include <random>
#include "Input_Coordinates.h"
const int BOARD_DIMENSION = 10;
const int NUM_SHIPS = 5;

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
    Input_Coordinates ic;
    const std::string myarr[NUM_SHIPS] = {"Carrier", "BattleShip", "Cruiser", "Submarine", "Destroyer"};

public:
    void init_board();
    void display_board();
    void reset_board();

    void init_fleet();
    bool init_fleet_randomize();
    bool init_fleet_manual();
    bool init_fleet_file();

    bool board_set_values();
    bool check_if_occupied();

    void which_ship_present();
    static int getRandom(int min, int max);
};
#endif // BATTLESHIP_H
