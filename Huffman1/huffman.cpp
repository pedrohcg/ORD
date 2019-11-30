#include "huffman.hpp"

huffman::huffman(){
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
    int id, i, n = 0;

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
            n++;
            fila.push(nodes[i]);
        }
    }
    cout << "NUMERO " << n << endl;
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

    return raiz;
}
//****************************CREATECODE**************************
void huffman::createCodes(node *a, string code){
    if(a){
        if(a->esq == NULL && a->dir == NULL){
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
    outFile.open("result/" + file + ".huffman", ios::out | ios::binary);
    string in = "", m = "";
    unsigned char buffer;
    int count = 0, s, id;

    //Verifica se o arquivo foi aberto
    assert(outFile.is_open());
    assert(inFile.is_open());

//    for(s = 0; s < 256; s++){
//        outFile.put(nodes[s]->id);
//        outFile.put(nodes[s]->freq);
//    }


    //Pega o primeiro caractere do arquivo
    id = inFile.get();

    while(!inFile.eof()){
        //pega o codigo do caractere
        in = nodes[id]->code;
        //percorre o string
        for(char &c : in){

            int x = c - '0';

            //se x for igual a 1 muda a posicao do bit para a posicao do contador
            if(x == 1){
                buffer |= (1 << count);
            }
            //incrementa a posicao do bit
            count++;
            //cout << x << endl;
            //se o contador for igual a 8 coloca o byte no arquivo e reseta.
            if(count == 8){
                outFile.put(buffer);
                count = 0;
                buffer = 0;
            }
        }
        //Pega o proximo caractere
        id = inFile.get();
    }

    if(count != 0){
        outFile.put(buffer);
    }

    inFile.close();
    outFile.close();
}
//*******************************************************************************
void huffman::esvaziar(){
    while(!fila.empty()){
        node *a = fila.top();
        cout << "L1 " << a->id << endl;
        cout << "F1 " << a->freq << endl;
        fila.pop();
    }
}
//*************************************DECOMPRESS*********************************
void huffman::decompress(string file){
    inFile.open(file, ios::in | ios::binary);
    outFile.open(file + ".decoded", ios::out);
    int count = 7, b, f = 0;
    unsigned char id;
    string c = "", t = "";
    node *a = raiz;

    assert(inFile.is_open());
    assert(outFile.is_open());

    id = inFile.get();
    t = writeByte(id);

    while(!inFile.eof()){
        //cout << t << endl;
        for(b = 0; b < t.size()/2; b++){
            swap(t[b], t[t.size() - b - 1]);
        }
        c += t;
        id = inFile.get();
        t = writeByte(id);

    }

    //cout << c << endl;

    for(char &l : c){
        int x = l - '0';
        //cout << a->freq << endl;
        if(a->esq == NULL && a->dir == NULL){
            outFile.put(a->id);
            //cout << "A" << a->code << endl;
            //cout << "RAIZ" << endl;
            a = raiz;
        }

        if(x == 0){
            a = a->esq;
            //cout << "ESQ" << endl;
        }

        if(x == 1){
            a = a->dir;
            //cout << "DIR" << endl;
        }
    }


    outFile.close();
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
