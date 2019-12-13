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
node* huffman::createTree(){
    int i, tam;
    //Fila de prioridade minima
    priority_queue <node*, vector<node*>, compare> temp(fila);

    tam = temp.size();

    //Cria a arvore
    while(!temp.empty()){
        raiz = new node();
        raiz->esq = temp.top();
        raiz->freq += temp.top()->freq;
        temp.pop();
        raiz->dir = temp.top();
        raiz->freq += temp.top()->freq;
        temp.pop();
        temp.push(raiz);
    }

    return temp.top();
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
    FILE *fptr = fopen("result/teste3.txt.huffman", "wb");
    string in = "", m = "";
    unsigned char buffer, id;
    int count = 0, s, nb = 0;
    unsigned int freq;

    //Verifica se o arquivo foi aberto
    if(!fptr){return;}
    assert(inFile.is_open());

    for(s = 0; s < 256; s++){
        fwrite(&nodes[s]->freq, sizeof(unsigned), 1, fptr);
    }
    fclose(fptr);

    outFile.open("result/" + file + ".huffman", ios::app | ios::binary);

    //Pega o primeiro caractere do arquivo
    id = inFile.get();
    nb++;

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
                nb++;
            }
        }
        //Pega o proximo caractere
        id = inFile.get();
    }

    if(count != 0){
        outFile.put(buffer);
        nb++;
    }

    cout << "NUMERO BUFFERS " << nb << endl;

    inFile.close();
    outFile.close();
}
//*****************************DECOMPRESS****************************************
void huffman::decompress(string file){
    FILE *fptr = fopen("result/teste3.txt.huffman", "rb");
    outFile.open(file + ".decoded", ios::out);
    int b, f = 0;
    unsigned char id;
    string t = "";
    node *a, *r;

    assert(outFile.is_open());
    if(!fptr){
        return;
    }

    int aux = 0;
    long unsigned int simbolosT = 0, simbolosL = 0;
    //Le o vetor de frequencia armazenado no arquivo
    for(b = 0; b < 256; b++){
        fread(&aux, sizeof(unsigned), 1, fptr);
        //cout << aux << endl;
        nodes[b]->freq = aux;
        //Coloca as folhas que tem uma frequencia diferente de 0 na fila de prioridade
        if(nodes[b]->freq != 0){
            fila.push(nodes[b]);
            simbolosT += aux;
        }
    }
    //Guarda onde esta no arquivo
    int pos = ftell(fptr);

    fclose(fptr);
    //Recria a arvore e os codigos
    r = createTree();
    createCodes(r, "");
    a = r;
    //printTree(a);

    inFile.open(file, ios::in | ios::binary);

    assert(inFile.is_open());

    inFile.seekg(pos);

    id = inFile.get();
    //Transforma o byte em um string de bits
    t = writeByte(id);
    f++;

    while(!inFile.eof()){
        //Inverte o string
        for(b = 0; b < t.size()/2; b++){
            swap(t[b], t[t.size() - b - 1]);
        }

        for(char &l : t){
            //Se achar uma folha com letra escreve a letra no arquivo
            if(a->esq == NULL && a->dir == NULL){
                outFile.put(a->id);
                a = r;
                simbolosT--;
            }

            //Se o bit for 0 vai pra esquerda e se for 1 vai pra direita
            switch(l){
                case '0':
                    a = a->esq;
                    break;
                case '1':
                    a = a->dir;
                    break;
            }
            if(simbolosT == 0){
                break;
            }
        }

        id = inFile.get();
        t = writeByte(id);
        f++;

        if(simbolosT == 0){
            break;
        }
    }

    cout << "BUFFERS LIDOS " << f << endl;

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
