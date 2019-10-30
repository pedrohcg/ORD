#include <stdio.h>

//****PROTOTIPOS***********
void buildMaxHeapfy(int[], int);
void maxHeapfy(int[], int);
void heapSort(int[], int);
void mostrar(int[], int);
void encherVetor(int[], int);
//*************************
//******MAIN***************
main(){
    int tamanho, i;
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
        printf("VETORES DE EXEMPLO = 3\n");
        printf("SAIR = 4\n");
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
        }
        if(i == 4){
            break;
        }
   }
}

//*********************FUNCOES*******************
//***********************************************

//********************BUILDMAXHEAPFY*************
void buildMaxHeapfy(int vet[], int tam){
    int c;

    for(c = tam; c >= 0; c--){
       maxHeapfy(vet, c);
    }
}

//********************MAXHEAPFY******************
void maxHeapfy(int vet[], int tam){
    int raiz = (tam/2) - 1;                         //Raiz � o �ltimo n� com filhos da �rvore
    int maior;                                      //Guarda a posi��o do maior valor

    while(raiz >= 0){
        int l = raiz*2 + 1;                         //Elemento a esquerda da raiz
        int r = raiz*2 + 2;                         //Elemento a direita da raiz

        //Verifica se l est� dentro do vetor e se o valor em l � menor que o valor da raiz

        if((l < tam) && (vet[l] > vet[raiz])){
            maior = l;
        }

        else{
            maior = raiz;
        }

        //Verifica se r est� dentro do vetor e se o valor em r � menor que o valor da raiz

        if((r < tam) && (vet[r] > vet[maior])){
            maior = r;
        }

        if(maior != raiz){
            //Troca a posi��o do maior valor pelo valor da raiz
            int aux = vet[maior];
            vet[maior] = vet[raiz];
            vet[raiz] = aux;
        }

        if((r < tam) && (l < tam)){
            //Deixa o maior valor sempre a esquerda
            if(vet[r] > vet[l]){
                int aux = vet[r];
                vet[r] = vet[l];
                vet[l] = aux;
            }
        }
        raiz--;                                     //Decrementa a posi��o da raiz
    }
}
//**********************************************

//*********************HEAPSORT*****************
void heapSort(int vet[], int tam){
    int i, c, aux;

    buildMaxHeapfy(vet, tam);                        //Cria uma heap m�ximo inicial

    c = tam;

    for(i = tam - 1; i > 0; i--){
        //Troca o primeiro valor pelo �ltimo
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;

        //Diminui o tamanho do vetor
        c -= 1;

        //Ordena o vetor

        maxHeapfy(vet, c);
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
void encherVetor(int vet[], int tam){
    int c, i;

    for(c = 0; c < tam; c++){
        printf("DIGITE UM VALOR PARA SER ADICIONADO AO VETOR\n");
        scanf(" %i", &i);
        vet[c] = i;
    }
}
