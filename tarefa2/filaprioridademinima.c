#include <stdio.h>
#include <math.h>
int tam;
//***************PROTÓTIPOS*****************
void buildMinHeapfy(int[]);
void minHeapfy(int[], int);
void mostrar(int[]);
int heapMinimo(int[]);
int heapExtractMin(int[]);
int pai(int[], int, int);
void heapDrecreaseKey(int[], int, int);
void minHeapInsert(int[], int);
//******************MAIN********************
main(){
    FILE *fptr;
    int i, t;

    fptr = fopen("dij10.txt", "r");

    //Verifica se o arquivo foi aberto.
    if(!fptr){return;}

    fscanf(fptr, " %d", &tam);

    tam = (tam*(tam-1))/2;

    int vet[tam];                    //Array que armazena todos os pesos

    //Pega as distâncias do arquivo e as armazena em um array.
    for(i = 0; i < tam; i++){
        fscanf(fptr, " %d", &vet[i]);
    }

    buildMinHeapfy(vet);
    printf("MINHEAPFY: ");
    mostrar(vet);
    t = heapMinimo(vet);
    printf("HEAPMINIMO: %d\n", t);
    t = heapExtractMin(vet);
    buildMinHeapfy(vet);
   printf("HEAPEXTRACTMIN: %d\n", t);
    heapDecreaseKey(vet, 8, 7);
    buildMinHeapfy(vet);
    printf("VETOR: ");
    mostrar(vet);
    minHeapInsert(vet, 100);
    buildMinHeapfy(vet);
    printf("VETOR FINAL: ");
    mostrar(vet);

    fclose(fptr);

}
//***************FUNÇÕES************************
//********************BUILDMINHEAPFY*************
void buildMinHeapfy(int vet[]){
    int c, t2;

    for(c = tam - 1; c >= 0; c--){
       minHeapfy(vet, c);
    }
}

//********************MINHEAPFY******************
void minHeapfy(int vet[], int tam2){
    int raiz = (tam2/2);                            //Raiz é o último nó com filhos da árvore
    int menor;                                      //Guarda a posição do menor valor

    while(raiz >= 0){
        int l = raiz*2 + 1;                         //Elemento a esquerda da raiz
        int r = raiz*2 + 2;                         //Elemento a direita da raiz

        //Verifica se l está dentro do vetor e se o valor em l é menor que o valor da raiz

        if((l < tam) && (vet[l] < vet[raiz])){
            menor = l;
        }

        else{
            menor = raiz;
        }

        //Verifica se r está dentro do vetor e se o valor em r é menor que o valor da raiz

        if((r < tam) && (vet[r] < vet[menor])){
            menor = r;
        }

        if(menor != raiz){
            //Troca a posição do maior valor pelo valor da raiz
            int aux = vet[menor];
            vet[menor] = vet[raiz];
            vet[raiz] = aux;
        }

        raiz--;                                     //Decrementa a posição da raiz
    }

}
//***********************MOSTRAR****************
//Mostra todos os valores no vetor
void mostrar(int vet[]){
    int c = 0;

    for(c; c < tam; c++){
        printf("%i ", vet[c]);
    }
    printf("\n");
}

//************************HEAPMINIMO***************
int heapMinimo(int vet[]){
    return vet[0];
}
//*********************HEAPEXTRACTMIN**************
int heapExtractMin(int vet[]){
    int min;

    if(tam < 1){return;}

    min = vet[0];
    vet[0] = vet[tam - 1];
    tam -= 1;
    minHeapfy(vet, tam);
    return min;
}
//*********************HEAPINCRESEKEY****************
void heapDecreaseKey(int vet[], int i, int chave){
    if(chave > vet[i]){
        return;
    }
    vet[i] = chave;

    int PAI = pai(vet, i, tam);

    while((i > 0) && (vet[PAI] > vet[i])){
        int aux = vet[PAI];
        vet[PAI] = vet[i];
        vet[i] = aux;
        i = PAI;
    }
}
//**************************PAI**********************
int pai(int vet[], int i, int tam){
    return floor((i - 1)/2);
}
//***********************MINHEAPINSERT********************
void minHeapInsert(int vet[], int chave){
    tam++;
    vet[tam - 1] = 9999999;
    heapDecreaseKey(vet, tam - 1, chave);
}
