#include <iostream>
#include <fstream>
#include <assert.h>
#include "huffman.hpp"

using namespace std;

int main(){
    huffman *h = new huffman();
    //Codification
    h->createQueue("teste3.txt");
    node *a;
    a = h->createTree();
    h->createCodes(a, "");
    h->printTree(a);
    h->compress("teste3.txt");
    //Decodification
    h->decompress("result/teste3.txt.huffman");
    //file.close();

   return 0;
}
