#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <map>
#include "node.h"

using namespace std;

class huffman{
    private:
        ofstream outFile;
        ifstream inFile;
        priority_queue <int, vector<int>, greater<int>> fila;
        node* folhas[256];
        unsigned int frequency[256];
        unsigned char buffer;
        int c;

    public:
        huffman();
        void writeByte(string f);
};

#endif
