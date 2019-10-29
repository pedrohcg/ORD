#include <stdio.h>

//****PROTOTIPOS***********
void buildMaxHeapfy(int[], int);
void maxHeapfy(int[], int);
void heapSort(int[], int);
void mostrar(int[], int);
//*************************
//******MAIN***************
main(){
    int tamanho, i;


    printf("DIGITE O TAMANHO DO VETOR\n");
    scanf(" %i", &tamanho);

    int vet[tamanho];

   while(1){
        printf("HEAP MAXIMO = 1\n");
        printf("HEAPSORT = 2\n");
        printf("SAIR = 3\n");
        scanf(" %i", &i);

        switch(i){
            case 1:
                buildMaxHeapfy(vet, tamanho);
            break;
            case 2:
                heapSort(vet, tamanho);
            break;
        }
        if(i == 3){
            break;
        }
   }
}

//*********************FUNCOES*******************
//***********************************************

//********************BUILDMAXHEAPFY*************
void buildMaxHeapfy(int vet[], int tam){
    int c = 0;

    for(c; c < tam; c++){
        int i;

        printf("DIGITE UM VALOR PARA SER ADICIONADO AO VETOR\n");
        scanf(" %i", &i);
        vet[c] = i;
    }

    maxHeapfy(vet, tam);
    mostrar(vet, tam);
}

//********************MAXHEAPFY******************
void maxHeapfy(int vet[], int tam){
    int raiz = (tam/2) - 1;                         //Raiz � o �ltimo n� com filhos da �rvore
    int maior = 0;                                  //Vari�vel auxiliar para guardar um valor durante uma troca de valores

    while(raiz >= 0){
        int l = raiz*2 + 1;                         //Elemento a esquerda da raiz
        int r = raiz*2 + 2;                         //Elemento a direita da raiz

        //Verifica se l est� dentro do vetor e se o valor em l � menor que o valor da raiz

        if((l < tam) && (vet[l] > vet[raiz])){
            //Se for menor troca a posi��o dos valores
            maior = vet[l];
            vet[l] = vet[raiz];
            vet[raiz] = maior;
        }

        //Verifica se r est� dentro do vetor e se o valor em r � menor que o valor da raiz

        if((r < tam) && (vet[r] > vet[raiz])){
            //Se for menor troca a posi��o dos valores
            maior = vet[r];
            vet[r] = vet[raiz];
            vet[raiz] = maior;
        }

        raiz--;                                     //Decrementa a posi��o da raiz
    }
}
//**********************************************

//*********************HEAPSORT*****************
void heapSort(int vet[], int tam){
    int i, aux;

    buildMaxHeapfy(vet, tam);                        //Cria uma heap m�ximo inicial

    for(i = tam - 1; i > 0; i--){
        //Troca o primeiro valor pelo �ltimo
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;

        //Diminui o tamanho do vetor
        tam -= 1;

        //Ordena o vetor

        maxHeapfy(vet, tam);
    }
    //Mostra o �ltimo valor no vetor
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
//**********************************************
