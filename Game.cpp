//
// Created by kd2ma on 1/4/2022.
//
#include <map>
#include <iterator>
#include <utility>
#include <fstream>
#include "Game.h"
using std::map;

void Game::start_game() {
    player1 = new Game;
    player2 = new Game;
    player1->standing_ships = 17;
    player2->standing_ships = 17;

    string input;

    cout << setw(25) << "====================\n";
    cout << setw(25) << "Game of Battle Ships\n";
    cout << setw(25) << "====================\n";

    player1->init_board();
    player2->init_board();
    cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
    cout << setw(25) << "Player 2 Board: \n" , player2->display_board();
    player1->init_fleet();
    player2->init_fleet();
    cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
    cout << setw(25) << "Player 2 Board: \n" , player2->display_missed_board();

    cout << "How would whom would like to play against? Select from human/computer/simulate: ";
    cin >> input;
    if (input == "human") {
        play_vs_human();
    } else if (input == "computer") {
        play_vs_computer();
    } else if (input == "simulate") {
        play_computer_vs_computer();
    }
}

bool Game::attack(Input_Coordinates& ic) {
    if(update_ship(ic)) {
        cout << "Hit!\n";
        standing_ships--;
    } else {
        cout << "Miss!\n";
    }
    return false;
}

bool Game::is_winner() const {
    if (standing_ships < 1) {
        return true;
    }
    return false;
}

bool Game::is_not_tried(Input_Coordinates ic) {
    std::ofstream fout;
    fout.open("mylog.txt", std::ios::out | std::ios::app);
    std::multimap<int, int>::iterator itr;
    bool present = false;
    for (itr = mymap.begin(); itr != mymap.end(); itr++) {
        if (itr->first == ic.x && itr->second == ic.y) {
            present = true;
        }
    }
    if (!present) {
        mymap.insert(std::pair<int,int>(ic.x, ic.y));
    } else {
        cout << "Coordinates X = " << ic.x << " Y =  " << ic.y << "are already attacked, try new coordinate:\n";
        fout << "Coordinates X = " << ic.x << " Y =  " << ic.y << "are already attacked, try new coordinate:\n";

    }
    for (itr = mymap.begin(); itr != mymap.end(); itr++) {
        std::cout << "Pair: " << itr->first << "," << itr->second << endl;
        fout << "Pair: " << itr->first << "," << itr->second << endl;

    }
    fout << "\n\n\n";
    return present;
}

void Game::play_vs_human() {
    Input_Coordinates ic;
    while (is_winner()) {
        cout << "(Player 1 turn) ";
        do {
            cin >> ic.x;
            cin >> ic.y;
        } while (player1->is_not_tried(ic));

        player2->attack(ic);
        cout << setw(25) << "Player 2 Board: \n" , player2->display_board();
        cout << setw(25) << "Player 2 Board: \n" , player2->display_missed_board();

        if (player2->is_winner()) {
            cout << "Player 1 is winner!\n";
            cout << "Player 2 : standing ships : " << player2->standing_ships;
            cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Player 2 Board: \n" , player2->display_board();
            cout << setw(25) << "Player 2 MISSED Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
        cout << "(Player 2 turn) ";
        do {
            cin >> ic.x;
            cin >> ic.y;
        } while (player2->is_not_tried(ic));
        player1->attack(ic);
        cout << setw(25) << "Player 1 Board: \n" , player1->display_board();

        if (player1->is_winner()) {
            cout << "Player 2 is winner!\n";
            cout << "Player 1 : standing ships : " << player1->standing_ships;
            cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Player 2 Board: \n" , player2->display_board();
            cout << setw(25) << "Player 2 MISSED Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
    }
}

void Game::play_vs_computer() {
    Input_Coordinates ic;
    while (is_winner()) {
        cout << "(Player 1 turn) ";
        do {
            cin >> ic.x;
            cin >> ic.y;
        } while (player1->is_not_tried(ic));
        player2->attack(ic);
        cout << setw(25) << "Computer Board: \n" , player2->display_board();
        cout << setw(25) << "Computer Missed Board: \n" , player2->display_missed_board();
        if (player2->is_winner()) {
            cout << "Player 1 is winner!\n";
            cout << "Computer : standing ships : " << player2->standing_ships;
            cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Computer Board: \n" , player2->display_board();
            cout << setw(25) << "Computer Missed Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
        cout << "(Computer turn) ";
        do {
            ic.x = getRandom(0,9);
            ic.y = getRandom(0,9);
        } while (player2->is_not_tried(ic));
        player1->attack(ic);
        cout << setw(25) << "Player 1 Board: \n" , player1->display_board();

        if (player1->is_winner()) {
            cout << "Player 2/Computer is winner!\n";
            cout << "Player 1 : standing ships : " << player1->standing_ships;
            cout << setw(25) << "Player 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Computer Board: \n" , player2->display_board();
            cout << setw(25) << "Computer Missed Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
    }
}

void Game::play_computer_vs_computer() {
    Input_Coordinates ic;
    while (is_winner()) {
        cout << "(Computer 1 turn) ";
        do {
            ic.x = getRandom(0,9);
            ic.y = getRandom(0,9);
        } while (player1->is_not_tried(ic));
        player2->attack(ic);
        cout << setw(25) << "Computer 2 Board: \n" , player2->display_board();
        cout << setw(25) << "Computer 2 Missed Board: \n" , player2->display_missed_board();
        if (player2->is_winner()) {
            cout << "Computer 1 is winner!\n";
            cout << "Computer 2 : standing ships : " << player2->standing_ships;
            cout << setw(25) << "Computer 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Computer 2 Board: \n" , player2->display_board();
            cout << setw(25) << "Computer 2 Missed Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
        cout << "(Computer 2 turn) ";
        do {
            ic.x = getRandom(0,9);
            ic.y = getRandom(0,9);
        } while (player2->is_not_tried(ic));
        player1->attack(ic);
        cout << setw(25) << "Computer 1 Board: \n" , player1->display_board();

        if (player1->is_winner()) {
            cout << "Computer 2 is winner!\n";
            cout << "Computer 1 : standing ships : " << player1->standing_ships;
            cout << setw(25) << "Computer 1 Board: \n" , player1->display_board();
            cout << setw(25) << "Computer 2 Board: \n" , player2->display_board();
            cout << setw(25) << "Computer 2 Missed Board: \n" , player2->display_missed_board();
            system("PAUSE");
            exit(1);
        }
    }
}



