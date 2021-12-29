#include <iostream>

#include "BattleShips.h"

int main() {
    BattleShips player1, player2;
    player1.init_board(); player2.init_board();
    cout << setw(25) << "Player 1 Board: \n" , player1.display_board();
    cout << setw(25) << "Player 2 Board: \n" , player2.display_board();
    player1.init_board_manual();
    player1.display_board();
    return 0;
}
