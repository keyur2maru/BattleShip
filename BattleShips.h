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

class BattleShips {
private:
    int player1_ships, player2_ships;
    vector<vector<string>> board;
    vector<vector<int>> missed_board;

public:
    void init_board();
    void init_board_manual();
    void display_board();

    bool board_set_values(int& direction, int& x, int& y, int& i);
};
#endif // BATTLESHIP_H
