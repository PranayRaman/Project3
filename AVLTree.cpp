#include "AVLTree.h"

// Return a node's height (accounting for nullptr)
int AVLTree::height(Node* node) {
    return (node != nullptr) ? node->height : 0;
}

// Calculate balance factor for a node based on its children
// *Source: Amanpreet Kapoor - AVL Trees Powerpoint (trees-3.pdf, slide 42)
int AVLTree::balanceFactor(Node* node) {
    return height(node->left) - height(node->right);
}

// Helper function for rotations and insert(); updates height based on children
// *Source: Amanpreet Kapoor - Trees Powerpoint (trees-1.pdf, slide 18)
void AVLTree::updateHeight(Node* node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}


// Left Rotation of node
// *Source: John Gionti - Stepik 5.1.1 solution
Node* AVLTree::rotateLeft(Node* node) {
    Node* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;
    updateHeight(node);
    updateHeight(newParent);
    return newParent;
}

// Right Rotation of node
// *Source: John Gionti - Stepik 5.1.1 solution
Node* AVLTree::rotateRight(Node* node) {
    Node* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    updateHeight(node);
    updateHeight(newParent);
    return newParent;
}

// Left Right Rotation of node (Left rotation on left child, then right rotation)
// *Source: John Gionti - Stepik 5.1.1 solution
Node* AVLTree::rotateLeftRight(Node* node) { 
    node->left = rotateLeft(node->left);
    node = rotateRight(node);
    return node;
}

// Right Left Rotation of node (Right rotation on right child, then left rotation)
// *Source: John Gionti - Stepik 5.1.1 solution
Node* AVLTree::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    return node;
}


// Helper function for insertHelper(); check for and perform rebalance on tree
// *Source: Amanpreet Kapoor - AVL Trees Powerpoint (trees-3.pdf, slide 43)
Node* AVLTree::balance(Node* node) {
    if (balanceFactor(node) > 1) {
        // Case 1: Left Left tree
        if (balanceFactor(node->left) > 0)
            return rotateRight(node);
        // Case 2: Left Right tree
        else if (balanceFactor(node->left) < 0)
            return rotateLeftRight(node);
    }
    else if (balanceFactor(node) < -1) {
        // Case 3: Right Left tree
        if (balanceFactor(node->right) > 0)
            return rotateRightLeft(node);
        // Case 4: Left Right tree
        else if (balanceFactor(node->right) < 0)
            return rotateLeft(node);
    }
    return node;
}

// Helper function for insert(); iterate with recursion to insert node
Node* AVLTree::insertHelper(Node* node, Game& game, int& id) {
    if (node == nullptr) {
        std::cout << "successful" << std::endl;
        return new Node(game, id);
    }

    // Iterate downward until target id is found (or not)
    else if (id > node->id)
        node->right = insertHelper(node->right, game, id);
    else if (id < node->id)
        node->left = insertHelper(node->left, game, id);
    else 
        std::cout << "unsuccessful" << std::endl;

    // Update heights
    updateHeight(node);

    // Check for rotations with balanceFactor() x
    // Perform rotations if necessary
    node = balance(node);

    return node;
}

// Create a new node and add to Tree, then balance if necessary
void AVLTree::insert(Game& game, int id) {
    root = insertHelper(root, game, id);
}


// Helper function for remove() and removeInorder(); search for id and delete if found
// input bool firstPass is hardcoded to prevent double output if deleted node is replaced by inorder successor
// *Source: Amanpreet Kapoor - Binary Search Trees Powerpoint (trees-2.pdf, slide 13)
Node* AVLTree::removeHelper(Node* node, int& id, bool firstPass) {
    if (node == nullptr) {
        std::cout << "unsuccessful" << std::endl;
        return node;
    }

    if (id > node->id)
        node->right = removeHelper(node->right, id, firstPass);
    else if (id < node->id)
        node->left = removeHelper(node->left, id, firstPass);
    else {                                                      // Found node to delete; handle based on # children
        if (firstPass) std::cout << "successful" << std::endl;
        Node* temp = nullptr;
        if (node->left == nullptr) {                 // 1 child (left) or 0 children
            temp = node->right;                         // Delete node and replace with child
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {           // 1 child (right) or 0 children
            temp = node->left;                          // Delete node and replace with child
            delete node;
            return temp;
        }

        std::stack<Node*> s;                        // 2 children: inorder successor; swap nodes and delete the inorder successor
        s.push(node->right);
        while (s.top()->left != nullptr) {
            s.push(s.top()->left);
        }

        temp = s.top();
        node->game.name = temp->game.name;
        node->id = temp->id;
        node->right = removeHelper(node->right, temp->id, false);
    }
    updateHeight(node);
    return node;
}

// Search for node by id, then delete if found (similar to search(id))
void AVLTree::remove(int id) {
    root = removeHelper(root, id, true);
}


// Helper function for search(id); iterate with recursion to find node
void AVLTree::searchHelper(Node* node, int& id) {
    if (node == nullptr) {
        std::cout << "unsuccessful" << std::endl;
    }

    else if (id == node->id)
        std::cout << node->game.name << std::endl;
    else if (id > node->id)
        return searchHelper(node->right, id);
    else
        return searchHelper(node->left, id);
}

// Search for node with a particular id
void AVLTree::search(int id) {
    searchHelper(root, id);
}

//Searching for Developer
void AVLTree::searchDevHelper(Node* node, string& Dev) {
    if (node == nullptr)
        return;
    
    for(int i =0; i< node->game.developers.size(); i++){

            if(Dev==node->game.developers[i]){
                cout<<node->game.developers[i];
            }
    }
    searchDevHelper(node->left, Dev);
    searchDevHelper(node->right, Dev);
    
}

// Search for node with a particular id
void AVLTree::searchDev(string Dev) {
    searchDevHelper(root, Dev);
}



// Helper function for nameSearchHelper(); create a string that pads leading 0's up to 8 digits
std::string AVLTree::toIdString(int& id) {
    int temp = id, digits = 0;
    const int MAX_DIGITS = 8;
    while (temp > 0) {
        temp /= 10;
        ++digits;
    }
    std::string idString(MAX_DIGITS-digits, '0');
    idString.append(std::to_string(id));

    return idString;
}

// Helper function for search(name); use preorder traversal and print name each time it matches
void AVLTree::nameSearchHelper(Node* node, std::string& name, std::string& idList) {
    if (node == nullptr)
        return;
    
    if (node->game.name == name) {
        idList += toIdString(node->id) + '\n';
    }
    
    nameSearchHelper(node->left, name, idList);
    nameSearchHelper(node->right, name, idList);
}

// Search for node with a particular name
// Not sorted by name, so will have to check EVERY node (using preorder traversal)
void AVLTree::search(std::string name) {
    std::string idList = "";
    nameSearchHelper(root, name, idList);

    if (idList != "")
        std::cout << idList;
    else std::cout << "unsuccessful" << std::endl;
}


// Helper function for printInorder(); recursively iterates through tree and creates list in a raw string
// *Source: Amanpreet Kapoor - Tree Traversals Powerpoint (trees-2.pdf, slide 17)
void AVLTree::inorderHelper(Node* node, std::string& nameList) {
    if (node == nullptr)
        return;
    
    inorderHelper(node->left, nameList);
    nameList += node->game.name + ", ";
    inorderHelper(node->right, nameList);
}

// Inorder traversal; cleans up raw string from helper and prints
void AVLTree:: printInorder() {
    std::string nameList = "";
    inorderHelper(root, nameList);
    if (root != nullptr)
        nameList.erase(nameList.size()-2, 2);
    std::cout << nameList << std::endl;
}


// Helper function for printPreorder(); recursively iterates through tree and creates list in a raw string
// *Source: Amanpreet Kapoor - Tree Traversals Powerpoint (trees-2.pdf, slide 17)
void AVLTree::preorderHelper(Node* node, std::string& nameList) {
    if (node == nullptr)
        return;
    
    nameList += node->game.name + ", ";
    preorderHelper(node->left, nameList);
    preorderHelper(node->right, nameList);
}

// Preorder traversal; cleans up raw string from helper and prints
void AVLTree::printPreorder() {
    std::string nameList = "";
    preorderHelper(root, nameList);
    if (root != nullptr)
        nameList.erase(nameList.size()-2, 2);
    std::cout << nameList << std::endl;
}


// Helper function for printPostorder(); recursively iterates through tree and creates list in a raw string
// *Source: Amanpreet Kapoor - Tree Traversals Powerpoint (trees-2.pdf, slide 17)
void AVLTree::postorderHelper(Node* node, std::string& nameList) {
    if (node == nullptr)
        return;
    
    postorderHelper(node->left, nameList);
    postorderHelper(node->right, nameList);
    nameList += node->game.name + ", ";
}

// Postorder traversal
void AVLTree::printPostorder() {
    std::string nameList = "";
    postorderHelper(root, nameList);
    if (root != nullptr)
        nameList.erase(nameList.size()-2, 2);
    std::cout << nameList << std::endl;
}


// Print number of levels in tree, which is just the root height
// Also accounts for empty root
void AVLTree::printLevelCount() {
    std::cout << ((root != nullptr) ? root->height : 0) << std::endl;
}


// Helper function for removeInorder; uses an inorder traversal until n is found to delete it
Node* AVLTree::removeInorderHelper(Node* node, int& i, int& n) {
    if (node == nullptr || i > n)
        return node;

    node->left = removeInorderHelper(node->left, i, n);
    ++i;
    if (i == n) {
        node = removeHelper(node, node->id, true);
        return node;
    }
    if (node != nullptr)
        node->right = removeInorderHelper(node->right, i, n);
    
    updateHeight(node);
    return node;
}

// Remove the nth node during an inorder traversal
void AVLTree::removeInorder(int n) {
    int i = -1;
    root = removeInorderHelper(root, i, n);
    if (i < n)
        std::cout << "unsuccessful" << std::endl;  
}