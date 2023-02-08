#pragma once
#include <string>

using namespace std;

class player_card
{
private:
	string name;
	int score;
	int id_number;
	static int next_id;

public:
	player_card();

	player_card(string name, int score);

	void display() const;

	string getName() const;

	int getScore() const;

	void increase_score(int score_increase);
};

