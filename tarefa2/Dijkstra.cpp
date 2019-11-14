#include <iostream>
#include <stdio.h>
#include <list>
#include <queue>

int tam;

//***************PROTÓTIPOS*****************
void inicializar(int[], int[]);
//******************MAIN********************
main(){
    FILE *fptr;
    int i, j;

    fptr = fopen("grafos/dij10.txt", "r");

    //Verifica se o arquivo foi aberto.
    if(!fptr){return 0;}


    fscanf(fptr, " %d", &tam);
    int m[tam][tam];

   std::list <std::pair<int, int> > *listaAdj;
   listaAdj = new std::list<std::pair<int, int> > [tam];

    int k = 0;
    //Le o arquivo e armazena os valores
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam; j++){
            if(j == k){
                m[i][j] = 0;

            }
            else if(j > k){
                fscanf(fptr, " %d", &m[i][j]);

            }
            else{
                m[i][j] = m[j][i];

           }
            listaAdj[i].push_back(std::make_pair(j, m[i][j]));
        }
        k++;

    }

//    for(i = 0; i < tam; i++){
//        for(j = 0; j < tam; j++){
//            printf("%d ", m[i][j]);
//        }
//        printf("\n");
//    }
    fclose(fptr);


    //Fila de prioridade
    std::priority_queue < std::pair<int, int>,std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > fila;
    //Vetor dos visitados e do peso
    int visitado[tam], D[tam];

    inicializar(D, visitado);

    fila.push(std::make_pair(D[0], 0));


    //Loop de dijkstra
    while(!fila.empty()){
        //Pega o 1 elemento da fila de prioridade
        std::pair<int, int> p = fila.top();
        int u = p.second;
        fila.pop();

        if(visitado[u] == 0){
            visitado[u] = 1;

            std::list<std::pair<int, int> >::iterator v;
            //Percorre todos os vertices e faz o relaxamento
            for(v = listaAdj[u].begin(); v != listaAdj[u].end(); v++){
                int m = (*v).first;
                int peso = (*v).second;

                if(D[m] > D[u] + peso){
                    D[m] = D[u] + peso;
                    fila.push(std::make_pair(D[m], m));
                }
            }
        }
     }

    printf("Resultado:%d", D[tam - 1]);


    return 0;
}

//*******************FUNÇÕES****************

//*****************INICIALIZAR**************
void inicializar(int d[], int visitado[]){
    int v;

    for(v = 0; v < tam; v++){
        d[v] = 99999999;
        visitado[v] = 0;
    }
    d[0] = 0;
}
