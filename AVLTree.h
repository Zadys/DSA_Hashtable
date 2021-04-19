#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <unordered_set>

#include "Game.h"

using namespace std;

struct Node
{
    Game game;

    Node* left = nullptr;
    Node* right = nullptr;
    unsigned int height;
    int balance;

    Node(Game game)
    {
        this->game = game;
        this->height = 1;
        this->balance = 0;
    }
};


class AVLTree 
{
private:
    Node* root;
    unsigned int nodeCount;
 
    Node* insertHelper(Node* node, Game& key);
    string inorderHelper(Node* node) const;
    Node* searchHelper(unsigned int key, Node* node) const;
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    void updateBalance(Node* node);
    void updateHeight(Node* node);


public:
    AVLTree();

    void insert(Game& g);
    void printLevelCount() const;
    Game& search(unsigned int rank) const;
    int size() const;
    Node* getRoot() const;
    void printInorder() const;
    void printGames(Game& Game) const;

    void traversal(Node* node, string& publisher, unordered_set<string>& set) const;

};

AVLTree::AVLTree()
{
    root = nullptr;
    nodeCount = 0;
}

Node* AVLTree::getRoot() const
{
    return root;
}


int AVLTree::size() const
{
    return nodeCount;
}

void AVLTree::insert(Game& g)
{
    if(root == nullptr)
    {
        nodeCount++;
        root = new Node(g);
        //cout << "successful\n";
    }
    else
        insertHelper(root, g);
}

Node* AVLTree::insertHelper(Node* node, Game& key)
{
    if(node == nullptr)
    {  
        nodeCount++;
        return new Node(key);
    }
    else if (key.rank == node->game.rank)
    {
        cout << "unsuccessful\n";
        return node;
    }
    else
    {
        if(key.rank < node->game.rank)
            node->left = insertHelper(node->left, key);

        if(key.rank > node->game.rank)
            node->right = insertHelper(node->right, key);
    }

    updateHeight(node);
    updateBalance(node);


    if(node->balance == 2)
    {
        if(node->left->balance == -1)
            node->left = rotateLeft(node->left);

        return rotateRight(node);
    }
    else if(node->balance == -2)
    {
        if(node->right->balance == 1)
            node->right = rotateRight(node->right);

        return rotateLeft(node);
    }

    return node;
}

Game& AVLTree::search(unsigned int rank) const
{
    return searchHelper(rank, root)->game;
}

Node* AVLTree::searchHelper(unsigned int rank, Node* node) const
{
    if(node == nullptr)
        return nullptr;

    else if(rank < node->game.rank)
        return searchHelper(rank, node->left);
    else if(rank > node->game.rank)
        return searchHelper(rank, node->right);
    else
        return node;

    return nullptr;
}

void AVLTree::printGames(Game& game) const
{
    unordered_set<string> set;
    traversal(root, game.publisher, set);

    for(string game: set)
        cout << game << '\n';
}


Node* AVLTree::rotateLeft(Node* node)
{
    Node* child = node->right;
    Node* gchild = child->left;

    child->left = node;
    updateHeight(child);
    node->right = gchild;
    updateHeight(node);

    if(node == root)
        root = child;


    updateHeight(gchild);
    updateBalance(child);
    updateBalance(node);

    return child;
}

Node* AVLTree::rotateRight(Node* node)
{
    
    Node* child = node->left;
    Node* gchild = child->right;
    
    child->right = node;
    updateHeight(child);

    node->left = gchild;
    updateHeight(node);

    if(node == root)
        root = child;

    updateHeight(gchild);
    updateBalance(child);
    updateBalance(node);

    return child;
}

void AVLTree::updateHeight(Node* node)
{
    if(node == nullptr) return;

    int left;
    int right;

    if(node->left)
        left = node->left->height;
    else
        left = 0;

    if(node->right)
        right = node->right->height;
    else
        right = 0;
    
    node->height = 1 + max(left, right);
}

void AVLTree::updateBalance(Node* node)
{
    if(node == nullptr) return;

    int left = 0;
    int right = 0;

    if(node->left)
        left = node->left->height;
    else
        left = 0;

    if(node->right)
        right = node->right->height;
    else
        right = 0;

    node->balance = left - right;
}


void AVLTree::printInorder() const
{
    string result = inorderHelper(root);
    result.pop_back();
    result.pop_back();
    cout << result << endl;
}

string AVLTree::inorderHelper(Node* node) const
{
    if(node == nullptr)
        return "";
    else
        return inorderHelper(node->left) + node->game.name + '\n' + inorderHelper(node->right);
}

void AVLTree::printLevelCount() const { cout << root->height << endl; }

void AVLTree::traversal(Node* node, string& publisher, unordered_set<string>& set) const
{
    if(!node)
        return;
    
    traversal(node->left, publisher, set);

    if(node->game.publisher == publisher)
        set.insert(node->game.name);

    traversal(node->right, publisher, set);
}