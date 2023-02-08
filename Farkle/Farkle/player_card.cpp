#include "player_card.h"
#include <iostream>

using namespace std;

int player_card::next_id = 1;

player_card::player_card(): name(""), score(0), id_number(next_id++) {}

player_card::player_card(string name, int score) : name(name), score(score), id_number(next_id++) {}

void player_card::display() const
{
	cout << "Name: " << name << " Score: " << score << endl;
}

string player_card::getName() const
{
	return name;
}

int player_card::getScore() const
{
	return score;
}

void player_card::increase_score(int score_increase)
{
	score = score + score_increase;
}
