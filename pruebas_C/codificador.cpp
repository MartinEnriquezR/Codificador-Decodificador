#include <iostream>
#include <stdlib.h>
using namespace std;

int main(){

//declarando el vector de mensaje
int mensaje[3] = {1,1,1};

//declaracion de la matriz generadora
int G[3][6] = {
    {1,1,1,1,0,0},
    {1,0,1,0,1,0},
    {1,1,0,0,0,1},
};

int aux[6] = {0,0,0,0,0,0};

//producto del vector por la matriz
for(int j=0;j<6;j++){
    for(int i=0;i<3;i++){
        aux[j] += mensaje[i]*G[i][j];
    }      
}

//resultado
cout << aux [0] << aux [1] << aux [2] << aux [3] << aux [4] << aux [5];
cout << "/";

int U[6] = {0,0,0,0,0,0};
//pasar el resultado a modulo 2
for (int i=0;i<6;i++){
    if(aux[i]%2 == 0)
        U[i]=0;
    else
        U[i]=1;
}

cout <<  U[0] << U[1] << U[2] << U[3] << U[4] << U[5];

}