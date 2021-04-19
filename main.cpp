#include "hashTable.h"
#include "AVLTree.h"

#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

void populateTrees();

void logic();


int main()
{

    logic();
    return 0;
}

void logic()
{
    hashTable table;

    unordered_map<string, AVLTree> trees;

    trees.emplace("Sports", *(new AVLTree));
    trees.emplace("Racing", *(new AVLTree));
	trees.emplace("Role-Playing", *(new AVLTree));
	trees.emplace("Puzzle", *(new AVLTree));
    trees.emplace("Misc", *(new AVLTree));
	trees.emplace("Shooter", *(new AVLTree));
	trees.emplace("Simulation", *(new AVLTree));
	trees.emplace("Action", *(new AVLTree));
	trees.emplace("Fighting", *(new AVLTree));
	trees.emplace("Adventure", *(new AVLTree));
	trees.emplace("Strategy", *(new AVLTree));
	trees.emplace("Platform", *(new AVLTree));
    
    ifstream file("vgsales.csv", ifstream::in);
    string line;
    getline(file, line);

    while(getline(file, line))
    {
        stringstream ss(line);
        
        string rank;
        getline(ss, rank, ',');

        string title;
        getline(ss, title, ',');

        string platform_0;
        getline(ss, platform_0, ',');

        string year;
        getline(ss, year, ',');

        string genre;
        getline(ss, genre, ',');

        string publisher;
        getline(ss, publisher, ',');

        string naSales;
        getline(ss, naSales, ',');

        string euSales;
        getline(ss, euSales, ',');

        string jpSales;
        getline(ss, jpSales, ',');

        string otherSales;
        getline(ss, otherSales, ',');

        string globalSales;
        getline(ss, globalSales);

        Game game(stoi(rank), title, genre, publisher, stof(globalSales));

        trees[genre].insert(game);

        table.insert(game);
    }

    // Game* game = table.find("Wii Play");
    // cout << game->genre;

    
    cout << "======== Game Genre Suggestion Program =========" << endl;
    
    string command = "";

    while(command != "q")
    {
        cout << "Please select an operation: " << endl;
        cout << "(1) Search Game and See Similar Titles" << endl;
        cout << "(2) View All Games in a Genre" << endl;
        cout << "Enter \"q\" to quit.\n\n";

        
        cin >> command;

        if(cin.fail())
        {
            cout << "Invalid Choice\n";
            cin.clear();
        }

        cin.sync();

        if (command == "1")
        {

            cout << "\nType in a title for recommendations or \"q\" to cancel selection:\n\n";

            string name;
            getline(cin, name);

            if(name == "q")
                continue;

            Game* game = table.find(name);

            while(!game && name != "q")
            {
                cout << "\nSorry, the title \"" << name << "\" does not exist.\n";
                cout << "Type in a title for recommendations or \"q\" to cancel selection:\n\n";
                getline(cin, name);
                game = table.find(name);
            }

            cout << "\nHere are some other " << game->genre << " games by " << game->publisher << ".\n\n";
            trees[game->genre].printGames(*game);

            cout << '\n';
        }
        else if(command == "2")
        {
            cout << "(1) Sports\n(2) Racing\n(3) Role-Playing\n(4) Puzzle\n(5) Shooter\n(6) Simulation\n";
            cout << "(7) Action\n(8) Fighting\n(9) Adventure\n(10) Strategy\n(11) Platformer\n\n";
            cout << "Select one of the genres above to view or type \"q\" to cancel selection.\n\n";
            cout << "Genre number: ";

            string choice;
            cin >> choice;
            cin.sync();

            string regex[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "q"};

            bool valid = false;

            for(int i = 0; i < 12; i++)
                if(choice == regex[i])
                    valid = true;
            
            while(!valid)
            {
                cout << "Sorry, that is not a recognized genre. Please try again or type \"q\" to cancel the selection.\n";
                cin >> choice;
                for(int i = 0; i < 12; i++)
                if(choice == regex[i])
                    valid = true;
            }

            if(choice == "1")
                trees["Sports"].printInorder();
            else if(choice == "2")
                trees["Racing"].printInorder();
            else if(choice == "3")
                trees["Role-Playing"].printInorder();
            else if(choice == "4")
                trees["Puzzle"].printInorder();
            else if(choice == "5")
                trees["Shooter"].printInorder();
            else if(choice == "6")
                trees["Simulation"].printInorder();
            else if(choice == "7")
                trees["Action"].printInorder();
            else if(choice == "8")
                trees["Figthing"].printInorder();
            else if(choice == "9")
                trees["Adventure"].printInorder();
            else if(choice == "10")
                trees["Strategy"].printInorder();
            else if(choice == "11")
                trees["Platform"].printInorder();
            else if(choice == "q")
                continue;

            cout << "\n\n";
        }
        else if(command == "q")
            continue;
        else
            cout << "Invalid choice, please try again.\n";
    }
    
}