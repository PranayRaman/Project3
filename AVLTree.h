#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include "Game.h"

// Node class to hold Game objects
// Each node has a game, id, node height, and pointers to its left and right children
// If a node is empty, it is assigned nullptr
struct Node {
    int id;
    std::string name;

    int height = 0;
    Node* left;
    Node* right;

    Node() : name(""), id(0), left(nullptr), right(nullptr) {};
    Node(std::string name, int id) : name(name), id(id), height(1), left(nullptr), right(nullptr) {};
    Node(std::string name, int id, Node* left, Node* right) : name(name), id(id), left(left), right(right) {};
};

// AVL Tree sorted by student IDs
// Only data is the root, which keeps track of its children
class AVLTree {
    Node* root;

    // CORE AVL TREE FUNCTIONS
    int height(Node* node);
    int balanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);

    // RECURSIVE HELPER FUNCTIONS
    Node* insertHelper(Node* node, std::string& name, int& id);
    Node* removeHelper(Node* node, int& id, bool firstPass);
    void searchHelper(Node* node, int& id);
    void nameSearchHelper(Node* node, std::string& name, std::string& idList);
    void inorderHelper(Node* node, std::string& nameList);
    void preorderHelper(Node* node, std::string& nameList);
    void postorderHelper(Node* node, std::string& nameList);
    Node* removeInorderHelper(Node* node, int& i, int& n);

    // HELPER FUNCTIONS
    void updateHeight(Node* node);
    Node* balance(Node* node);
    Node* getNodeReplacement(Node* node);
    std::string toIdString(int& id);
       
    public:
    void insert(std::string name, int id);
    void remove(int id);
    void search(int id);
    void search(std::string name);

    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder (int n);

    AVLTree() : root(nullptr) {};
};