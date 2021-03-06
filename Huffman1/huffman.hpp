#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <assert.h>
#include <vector>
#include <string>
#include <stdio.h>

#include "node.h"
#include "compare.h"

using namespace std;

class huffman{
    private:
        ofstream outFile;
        ifstream inFile;
        node* nodes[256];
        node* raiz;
        int frequency[256];
        priority_queue <node*, vector<node*>, compare> fila;
        void createNodes();

    public:
        huffman();
        string writeByte(int a);
        int readByte(string &i);
        void createQueue(string file);
        node* createTree();
        void compress(string file);
        void createCodes(node *a, string code);
        void printTree(node* a);
        void printTreeE(node* a, int i);
        void printTreeD(node* a, int i);
        void decompress(string file);
};

#endif
