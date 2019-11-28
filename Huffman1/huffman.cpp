#include "huffman.hpp"

huffman::huffman(){
    totalS = 0;
    createNodes();
}
//****************************writeByte**************************
string huffman::writeByte(int a){
    string aux = "";
    string r = "";
    int i;

    while(a){
        aux += ('0' + a%2);
        a /= 2;
    }

    r.append(8 - aux.size(), '0');

    for(i = aux.size() - 1; i >= 0; i--){
        r += aux[i];
    }

    return r;
}
//****************************readByte****************************
int huffman::readByte(string &i){
    int r = 0, j;

    for(j = 0; j < i.size(); j++){
        r = r*2 + i[j] - '0';
    }

    return r;
}
//****************************CREATENODES***************************
void huffman::createNodes(){
    int i;

    for(i = 0; i < 256; i++){
       nodes[i] = new node();
       nodes[i]->id = i;
       nodes[i]->freq = 0;
       frequency[i] = 0;
    }
}
//****************************CREATEQUEUE***************************
void huffman::createQueue(string file){
    int id, i;

    inFile.open(file, ios::in);
    //Verifica se o arquivo foi aberto
    assert(inFile.is_open());

    id = inFile.get();
    //Percorre todo o arquivo e conta a frequencia dos caracteres
    while(!inFile.eof()){
        nodes[id]->freq++;
        frequency[id]++;
        id = inFile.get();
    }
    //aaa
    //Coloca na fila de prioridade minima os caracteres presentes no arquivo
    for(i = 0; i < 256; i++){
        if(nodes[i]->freq != 0){
            fila.push(nodes[i]);
            totalS++;
        }
    }

    inFile.close();
}
//****************************CREATETREE***************************
node* huffman::createTree(string file){
    int i, tam;
    //Fila de prioridade minima
    priority_queue <node*, vector<node*>, compare> temp(fila);

    tam = temp.size();

    //Cria a arvore
    for(i = 0; i < tam; i++){
        raiz = new node();
        raiz->esq = temp.top();
        temp.pop();
        raiz->dir = temp.top();
        raiz->freq += raiz->esq->freq + raiz->dir->freq;
        temp.pop();
        temp.push(raiz);

    }

    return temp.top();
}
//****************************CREATECODE**************************
void huffman::createCodes(node *a, string code){
    if(a){
        if(a->id){
            a->code = code;
        }
        else{
            createCodes(a->esq, code + '0');
            createCodes(a->dir, code + '1');
        }
    }
}
//****************************COMPRESS****************************
void huffman::compress(string file){
    inFile.open(file, ios::in);
    outFile.open(file + "huffman", ios::out | ios::binary);
    string in = "", s = "";
    int i;

    //Verifica se o arquivo foi aberto
    assert(outFile.is_open());
    assert(inFile.is_open());

    in += fila.size();
    priority_queue<node*, vector<node*>, compare> temp(fila);

    //Armazena no arquivo as frequencias e codigos
    while(!temp.empty()){
        node *a = temp.top();
        in += a->id;
        in += a->freq;
        temp.pop();
    }

    outFile.write(in.c_str(), in.size());
    inFile.close();
    outFile.close();
}

void huffman::teste(string file){
    inFile.open(file, ios::in);

    int id, i = 0;

    id = inFile.get();
    i = inFile.get();

    while(!inFile.eof()){
        char c = id;
        cout << c << endl;
        cout << id << endl;
        id = inFile.get();
    }

    inFile.close();
}
//****************************PRINTTREE***************************
void huffman::printTree(node *a){
    int i = 0;

    if(a){
        cout << "RAIZ" << a->id << " " << a->freq << " POSICAO " << i << " CODIGO " << a->code << endl;
        printTreeE(a->esq, i+1);
        printTreeD(a->dir, i+1);
    }
}

void huffman::printTreeE(node *a, int i){
    if(a){
        cout << "ESQ " << a->id << " " << a->freq << " POSICAO " << i << " CODIGO " << a->code << endl;
        printTreeE(a->esq, i+1);
        printTreeD(a->dir, i+1);
    }
}

void huffman::printTreeD(node *a, int i){
    if(a){
        cout << "DIR " << a->id << " " << a->freq << " POSICAO " << i << " CODIGO " << a->code << endl;
        printTreeE(a->esq, i+1);
        printTreeD(a->dir, i+1);
    }
}
