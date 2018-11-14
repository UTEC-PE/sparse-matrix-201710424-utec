#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
struct Node {
    int x, y;
    T data;
    Node* next;
    Node* down;
};

#endif
