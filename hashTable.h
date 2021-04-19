
#include "Game.h"
#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <string>

using namespace std;

class hashTable
{

private:
    hash<string> hasher;
    int capacity;
    int size;
    float loadFactor = 0.6f;
    vector<list<Game>> buckets;

public:
    hashTable()
    {
        capacity = 100;
        size = 0;
        buckets.resize(capacity);
    }

    int getHash(Game game)
    {
        return hasher(game.name) % (capacity-1);
    }

    int getHash(string title)
    {
        return hasher(title) % (capacity -1);
    }

    void insert(Game game)
    {
        int index = getHash(game);

        if(has(game))
            return;

        buckets.at(index).push_back(game);

        size++;

        if((float)size/capacity >= loadFactor)
            rehash();
    }

    bool has(Game game)
    {
        int index = getHash(game);

        for(Game g : buckets.at(index))
            if(g == game)
                return true;

        return false;
    }

    bool has(string title)
    {
        int index = getHash(title);

        for(Game g : buckets.at(index))
            if(g.name == title)
                return true;

        return false;
    }

    void remove(Game game)
    {

        if(!has(game))
            return;

        int index = getHash(game);

        buckets.at(index).remove(game);
        size--;
    }

    Game* find(string title)
    {
        // if(!has(title))
        //     return nullptr;
        
        Game* g;

        int index = getHash(title);
        list<Game> list = buckets.at(index);

        for(auto it = list.begin(); it != list.end(); it++)
        {
            if(it->name == title)
            {
                g = new Game(it->rank, it->name, it->genre, it->publisher, it->sales);
                return g;
            }
        }

        return nullptr;
    }

    void rehash()
    {
        //cout << "Rehashing at size " << size << '\n';
        vector<Game> temp;
        for(list<Game> l : buckets)
            for(Game g : l)
                temp.push_back(g);
    
        capacity *= 2;
        buckets.clear();
        buckets.resize(capacity);

        for(Game g : temp)
            buckets.at(getHash(g)).push_back(g);

    }

    void print()
    {
        int i = 0;
        for(list<Game> l : buckets)
        {
            if(!l.empty())
            {
                cout << '[' << i << "]: ";
                for(Game g : l)
                    cout << g.rank << " -> ";

                cout << '\n';
            }
            i++;
        }
    }
};