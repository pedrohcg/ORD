#include <iostream>
#include <fstream>
#include <assert.h>
#include "huffman.hpp"

using namespace std;

int main(){
    huffman *h = new huffman();
//    ifstream file;
//    unsigned int frequency[256] = {};
//    int a;
//
//    file.open("teste.txt", ios::in);
//    assert(file.is_open());
//
//    a = file.get();
//
//    while(!file.eof()){
//        //Contador de frequencia de caractere
//        frequency[a]++;
//
//        string m = h->writeByte(a);
//        cout << m << endl;
//
//        char l = h->readByte(m);
//        cout << l << endl;
//
//        cout << "frequencia" << endl;
//        cout << frequency[a] << endl;
//
//        a = file.get();
//    }

    h->createQueue("generated.fib25");
    node *a;
    a = h->createTree("generated.fib25");
    h->createCodes(a, "");
    h->printTree(a);
    h->compress("generated.fib25");
    h->decompress("result/generated.fib25.huffman");
    //file.close();

   return 0;
}
