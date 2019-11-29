#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class node{
    public:
        unsigned char id;
        unsigned int freq;
        std::string code;
        node *esq;
        node *dir;
        node();
};

#endif // NODE_H
