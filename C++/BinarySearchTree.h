//
// Created by seanp on 14/12/2018.
//

#ifndef OBJECTORIENTEDPROGRAMMING_C_BINARYSEARCHTREE_H
#define OBJECTORIENTEDPROGRAMMING_C_BINARYSEARCHTREE_H

#include <vector>

template<class T>
struct node {
    T data;
    node *left;
    node *right;

    explicit node(T newData) {
        this->data = newData;
    }

    ~node() {
        delete (left);
        delete (right);
    }
};

template<class T>
class BST {
private:
    node<T> *rootNode;

    void recursiveInsert(T toAdd, node<T> *root) {
        if (toAdd < root->data) {
            if (!root->left) {
                root->left = new node<T>(toAdd);
                root->left->right = nullptr;
                root->left->left = nullptr;
            } else {
                recursiveInsert(toAdd, root->left);
            }
        } else {
            if (!root->right) {
                root->right = new node<T>(toAdd);
                root->right->left = nullptr;
                root->right->right = nullptr;
            } else {
                recursiveInsert(toAdd, root->right);
            }
        }
    }

    node<T> *recursiveFind(T toFind, node<T> *root) {
        if (!root) {
            return nullptr;
        } else if (root->data == toFind) {
            return root;
        } else {
            if (toFind < root->data) {
                return recursiveFind(toFind, root->left);
            } else {
                return recursiveFind(toFind, root->right);
            }
        }
    }

    void addBackToTree(node<T> *nodeToAdd) {
        insert(nodeToAdd->data);
        if (nodeToAdd->left) {
            addBackToTree(nodeToAdd->left);
        }

        if (nodeToAdd->right) {
            addBackToTree(nodeToAdd->right);
        }
    }

    node<T> *recursiveRemove(T toRemove, node<T> *root) {
        node<T> *previousNode = nullptr;
        node<T> *currentNode = root;
        bool found = false;

        while (!found) {
            if (currentNode->data == toRemove) {
                found = true;
            } else if (currentNode->data < toRemove) {
                previousNode = currentNode;
                currentNode = currentNode->right;
            } else {
                previousNode = currentNode;
                currentNode = currentNode->left;

            }
        }

        if (currentNode->right == nullptr) {
            if (previousNode->data < currentNode->left->data) {
                previousNode->right = currentNode->left;
            } else {
                previousNode->left = currentNode->left;
            }
        } else if (currentNode->left == nullptr) {
            if (previousNode->data < currentNode->right->data) {
                previousNode->right = currentNode->right;
            } else {
                previousNode->left = currentNode->right;
            }
        } else {
            if (previousNode->data < currentNode->right->data) {
                previousNode->right = currentNode->right;
            } else {
                previousNode->left = currentNode->right;
            }
            childReaddition(currentNode->left);
        }

        delete currentNode;
        return root;
    }

    void childReaddition(node<T> *child) {
        if (child == nullptr) {
            return;
        }
        node<T> *right = child->right;
        node<T> *left = child->left;
        insert(child->data);

        childReaddition(right);
        childReaddition(left);
    }

public:
    node<T> *getRootNode() {
        return rootNode;
    }

    std::vector <T> preOrder(node<T> *root) {
        std::vector <T> toReturn;
        if (root == nullptr) {
            return toReturn;
        }

        toReturn.push_back(root->data);
        std::vector <T> leftReturn = preOrder(root->left);
        std::vector <T> rightReturn = preOrder(root->right);

        for (auto &i: leftReturn) {
            toReturn.push_back(i);
        }

        for (auto &i: rightReturn) {
            toReturn.push_back(i);
        }

        return toReturn;
    }

    std::vector <T> postOrder(node<T> *root) {
        std::vector <T> toReturn;
        if (root == nullptr) {
            return toReturn;
        }

        std::vector <T> leftReturn = postOrder(root->left);
        std::vector <T> rightReturn = postOrder(root->right);
        toReturn.push_back(root->data);

        for (auto &i: leftReturn) {
            toReturn.push_back(i);
        }

        for (auto &i: rightReturn) {
            toReturn.push_back(i);
        }

        return toReturn;
    }

    std::vector <T> inOrder(node<T> *root) {
        std::vector <T> toReturn;

        if (root == nullptr) {
            return toReturn;
        }

        std::vector <T> leftReturn = inOrder(root->left);
        toReturn.push_back(root->data);
        std::vector <T> rightReturn = inOrder(root->right);

        for (int i = 0; i < leftReturn.size(); i++) {
            toReturn.push_back(leftReturn[i]);
        }

        for (int i = 0; i < rightReturn.size(); i++) {
            toReturn.push_back(rightReturn[i]);
        }

        return toReturn;
    }

    void insert(T toAdd) {
        if (rootNode) {
            recursiveInsert(toAdd, rootNode);
        } else {
            rootNode = new node<T>(toAdd);
            rootNode->right = nullptr;
            rootNode->left = nullptr;
        }
    }

    node<T> *find(T toFind) {
        if (!rootNode) {
            return nullptr;
        } else {
            if (rootNode->data == toFind) {
                return rootNode;
            } else if (toFind < rootNode->data) {
                return recursiveFind(toFind, rootNode->left);
            } else {
                return recursiveFind(toFind, rootNode->right);
            }
        }
    }

    int remove(T toRemove) {
        if (find(toRemove) != nullptr) {
            if (rootNode->data == toRemove) {
                node<T> *tempLeft = rootNode->left;
                node<T> *tempRight = rootNode->right;
                rootNode = tempLeft;
                if (!tempRight) {
                    //right node is null therefore no children and node has been deleted successfully.
                } else {
                    //add tempRight and its children back into the tree
                    addBackToTree(tempRight);
                }

            } else {
                rootNode = recursiveRemove(toRemove, rootNode);
            }
        } else {
            return 1; //item could not be found in the tree
        }
        return 0;
    }

    int delTree(node<T> *root) {
        int lReturn = 0, rReturn = 0;
        if (root->left != nullptr) {
            lReturn = delTree(root->left);
        } else if (root->right != nullptr) {
            rReturn = delTree(root->right);
        }

        delete (root);

        if (lReturn == 0 && rReturn == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    ~BST() {
        delete (rootNode);
    }
};


#endif //OBJECTORIENTEDPROGRAMMING_C_BINARYSEARCHTREE_H
