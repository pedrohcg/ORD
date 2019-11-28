#ifndef NODE_H
#define NODE_H

#include <iostream>

class node{
    public:
        char id;
        int freq;
        std::string code;
        node *esq;
        node *dir;
        node();
};

#endif // NODE_H
