#include <iostream>
#include <list>
#include <time.h>

using namespace std;

int main(){
    list<int> vet;
    list<int> vetAux;
    list<int>::iterator pos;
    list<int>::iterator pos2;
    int i;

    srand(time(NULL));
    //Preenche o vetor com números aleatórios
    for(i = 0; i < 20; i++){
        vet.push_front(rand());
    }

    //Printa vetor
    for(pos = vet.begin(); pos != vet.end(); pos++){
        cout << *pos << endl;
    }

    cout << endl;
    for(pos = vet.begin(); pos != vet.end(); pos++){
        //Se o vetor auxiliar estiver vazio coloca o elemento na primeira posicao
        if(vetAux.empty()){
                vetAux.push_front(*pos);
        }

        else{
            //Percorre todos os elementos do vetor auxiliar
            for(pos2 = vetAux.begin(); pos2 != vetAux.end(); pos2++){
                //Verifica se o elemento do vetor e menor que o elemento do vetor auxiliar
                if(*pos < *pos2){
                    vetAux.insert(pos2, *pos);
                    break;
                }
            }
            //Se percorrer ate o fim do vetor auxiliar significa que o vetor auxiliar nao tinha nenhum elemento menor que ele
            //Logo, coloca esse elemento no fim
            if(pos2 == vetAux.end()){
                vetAux.push_back(*pos);
            }
        }
    }

    //Printa o vetor final
    for(pos = vetAux.begin(); pos != vetAux.end(); pos++){
        cout << *pos << endl;
    }
}

