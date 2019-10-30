#include <stdio.h>

//****PROTOTIPOS***********
void buildMaxHeapfy(int[], int);
void maxHeapfy(int[], int, int);
void heapSort(int[], int);
void mostrar(int[], int);
void encherVetor(int[], int);
//*************************
//******MAIN***************
main(){
    int tamanho, i;
    FILE *fptr;
    int vet1[13] = {27, 17, 3, 16, 13, 10, 15, 7 , 12, 4, 8, 9, 0};
    int vet2[9] = {23, 17, 14, 6, 13, 10, 15, 7, 12};
    int vet3[4] = {7, 0, 4, 2};
    int vet4[4] = {8, 9, 5, 1};
    int vet5[4] = {3, 8, 8, 8};
    int vet6[4] = {9, 7, 8, 6};

    printf("DIGITE O TAMANHO DO VETOR\n");
    scanf(" %i", &tamanho);

    int vet[tamanho];

    while(1){
        printf("HEAP MAXIMO = 1\n");
        printf("HEAPSORT = 2\n");
        printf("VETORES DE TESTE = 3\n");
        printf("VETORES DE TESTE DO ARQUIVO = 4\n");
        printf("SAIR = 5\n");
        scanf(" %i", &i);

        switch(i){
            case 1:
                encherVetor(vet, tamanho);
                buildMaxHeapfy(vet, tamanho);
                mostrar(vet, tamanho);
            break;
            case 2:
                encherVetor(vet, tamanho);
                heapSort(vet, tamanho);
            break;
            case 3:
                buildMaxHeapfy(vet1, 13);
                printf("MAXHEAPFY: ");
                mostrar(vet1, 13);
                printf("\nHEAPSORT: ");
                heapSort(vet1, 13);
                printf("\n");

                buildMaxHeapfy(vet2, 9);
                printf("MAXHEAPFY: ");
                mostrar(vet2, 9);
                printf("\nHEAPSORT: ");
                heapSort(vet2, 9);
                printf("\n");

                buildMaxHeapfy(vet3, 4);
                printf("MAXHEAPFY: ");
                mostrar(vet3, 4);
                printf("\nHEAPSORT: ");
                heapSort(vet3, 4);
                printf("\n");

                buildMaxHeapfy(vet4, 4);
                printf("MAXHEAPFY: ");
                mostrar(vet4, 4);
                printf("\nHEAPSORT: ");
                heapSort(vet4, 4);
                printf("\n");

                buildMaxHeapfy(vet5, 4);
                printf("MAXHEAPFY: ");
                mostrar(vet5, 4);
                printf("\nHEAPSORT: ");
                heapSort(vet5, 4);
                printf("\n");

                buildMaxHeapfy(vet6, 4);
                printf("MAXHEAPFY: ");
                mostrar(vet6, 4);
                printf("\nHEAPSORT: ");
                heapSort(vet6, 4);
                printf("\n");
            break;
            case 4:
                fptr = fopen("couting.txt", "r");
                int tam, t, e;


                if(!fptr){return;}                      //Verifica se o arquivo foi realmente aberto

                fscanf(fptr, " %d", &tam);

                int vetArq[tam];

                for(t = 0; t < tam; t++){               //Enche o vetor com os números no arquivo
                    fscanf(fptr, " %d", &e);
                    vetArq[t] = e;
                }

                buildMaxHeapfy(vetArq, tam);
                printf("MAXHEAPFY: ");
                mostrar(vetArq, tam);
                printf("\nHEAPSORT: ");
                heapSort(vetArq, tam);
                printf("\n");

            break;
        }
        if(i == 5){
            break;
        }
   }
}

//*********************FUNCOES*******************
//***********************************************

//********************BUILDMAXHEAPFY*************
void buildMaxHeapfy(int vet[], int tam){
    int c, t2;

    t2 = tam;

    for(c = tam - 1; c >= 0; c--){
       maxHeapfy(vet, t2, c);
    }
}

//********************MAXHEAPFY******************
void maxHeapfy(int vet[], int tam, int tam2){
    int raiz = (tam2/2);                            //Raiz é o último nó com filhos da árvore
    int maior;                                      //Guarda a posição do maior valor

    while(raiz >= 0){
        int l = raiz*2;                             //Elemento a esquerda da raiz
        int r = raiz*2 + 1;                         //Elemento a direita da raiz

        //Verifica se l está dentro do vetor e se o valor em l é menor que o valor da raiz

        if((l < tam) && (vet[l] > vet[raiz])){
            maior = l;
        }

        else{
            maior = raiz;
        }

        //Verifica se r está dentro do vetor e se o valor em r é menor que o valor da raiz

        if((r < tam) && (vet[r] > vet[maior])){
            maior = r;
        }

        if(maior != raiz){
            //Troca a posição do maior valor pelo valor da raiz
            int aux = vet[maior];
            vet[maior] = vet[raiz];
            vet[raiz] = aux;
        }

        raiz--;                                     //Decrementa a posição da raiz
    }

}
//**********************************************

//*********************HEAPSORT*****************
void heapSort(int vet[], int tam){
    int i, c, aux;

    buildMaxHeapfy(vet, tam);                        //Cria uma heap máximo inicial

    c = tam;

    for(i = tam - 1; i > 0; i--){
        //Troca o primeiro valor pelo último
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;

        //Diminui o tamanho do vetor
        c -= 1;

        //Ordena o vetor

        maxHeapfy(vet, c, tam);
    }
    mostrar(vet, tam);
}

//***********************MOSTRAR****************
//Mostra todos os valores no vetor
void mostrar(int vet[], int tam){
    int c = 0;

    for(c; c < tam; c++){
        printf("%i ", vet[c]);
    }
    printf("\n");
}
//*******************ENCHERVETOR*******************
//Preenche o vetor com valores
void encherVetor(int vet[],int tam){
    int c, i;

    for(c = 0; c < tam; c++){
        printf("DIGITE UM VALOR PARA SER ADICIONADO AO VETOR\n");
        scanf(" %i", &i);
        vet[c] = i;
    }
}
