// Farkle.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "player_card.h"

using namespace std;

int player_count;
bool roll_again;
int dice_rolled;
int quantity;
int chosen_die;
int score_increase;
bool farkle;
bool end_game;
string name;
string another_die;
string saved_die;
string roll_or_save;
string save_die_or_farkle;
string winner;


void play_game(list<player_card> playerCards);
vector<int> roll_dice(int quantity);

int main()
{
    list<player_card> playerCards;

    // Set up scoreboard.
    cout << "How many players are there in this game: ";
    cin >> player_count;

    // Make a scorecard for each player.
    int cards_made = 0;
    while (cards_made < player_count) {
        cout << "Player Name: ";
        cin >> name;
        player_card new_card(name, 0);
        playerCards.push_back(new_card);
        cards_made++;
    }

    // Finally, start playing the game.
    play_game(playerCards);
}

void play_game(list<player_card> playerCards) {

    end_game = false;
    while (end_game == false) {
        // At the beginning of each round, display the current scoreboard.
        system("CLS");
        cout << "Scoreboard:" << endl;
        for_each(playerCards.begin(), playerCards.end(), [](auto& card) {
            card.display();
        });

        // This loop will go around for each player's turn.
        for_each(playerCards.begin(), playerCards.end(), [](auto& card) {

            // Display whose turn it is.
            name = card.getName();
            cout << name << "'s turn:" << endl;

            // Role the dice.
            int dice_count = 6;
            roll_again = true;
            vector<string> saved_dice;
            vector<int> results;
            farkle = false;
            while (roll_again == true) {

                // Get results and display them.
                results = roll_dice(dice_count);
                cout << "Dice Results: ";
                for (int i: results)
                {
                    cout << i << ", ";
                }
                cout << endl;

                // Have users pick dice to put aside.
                bool save_dice = true;
                while (save_dice == true) {
                    cout << "Pick a dice to put aside, or 'f' for farkle: ";
                    cin >> save_die_or_farkle;

                    // As long as user did not farkle, save the dice.
                    if (save_die_or_farkle != "f") {
                        saved_dice.push_back(save_die_or_farkle);
                        dice_count--;

                        // As long as there are still dice, give option to keep rolling dice.
                        cout << "Pick another dice? (y/n): ";
                        cin >> another_die;
                        if (another_die == "n") {
                            save_dice = false;
                        }
                    }
                    // If the user farkles, end all loops so they don't get any points.
                    else {
                        farkle = true;
                        save_dice = false;
                        roll_again = false;
                    }
                }
                // As long as the user does not farkle, give them the option to continue.
                if (farkle == false) {
                    // Ask the user if they would like to roll again or save their score.
                    cout << "Would you like to roll again, or save your score? ('r' for roll, 's' for save): ";
                    cin >> roll_or_save;

                    // If the user wants to save their score, end their turn loop, print out their saved dice, and update their score.
                    if (roll_or_save == "s") {
                        roll_again = false;
                        for (string i : saved_dice)
                        {
                            cout << i << ", ";
                        }
                        cout << endl;
                        cout << "Enter the score for these dice values: ";
                        cin >> score_increase;
                        card.increase_score(score_increase);

                        // If someone gets more than 10,000 points, they win.
                        if (card.getScore() >= 10000) {
                            winner = name;
                            end_game = true;
                        }
                    }

                    // If the player wants to roll again, but no more dice remain, they get to roll 6 new dice.
                    else if (roll_or_save == "r") {
                        if (dice_count <= 0) {
                            dice_count = 6;
                        }
                    }
                }
            }
        });
    }
    cout << "Game Over! " << winner << "wins!" << endl;
}

vector<int> roll_dice(int quantity) {

    // Set up random number generator in the range, and a vector to collect the results.
    srand(time(0));
    vector<int> results;
    dice_rolled = 0;
    while (dice_rolled < quantity)
    {
        results.push_back(rand() % 6 + 1);
        dice_rolled++;
    }
    return results;
}