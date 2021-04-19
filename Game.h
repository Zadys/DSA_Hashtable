#include <string>

using namespace std;

#ifndef GAME_H
#define GAME_H

struct Game {

	int rank;
	string name;
	string genre;
    string publisher;
    float sales;

    Game()
    {
        rank = -1;
        name = "";
        genre ="";
        publisher = "";
        sales = -1;
    }

	Game(int r, string n, string g, string p, float s)
    {

		rank = r;
		name = n;
		genre = g;
        publisher = p;
        sales = s;
	}

    bool operator==(const Game& g)
    {
        if(this->name.compare(g.name) == 0 && this->genre.compare(g.genre) == 0 && this->rank == g.rank && this->sales == g.sales)
            return true;

        return false;
    }

};

#endif