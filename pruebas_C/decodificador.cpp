#include <iostream>
#include <stdlib.h>
using namespace std;

//palabra recibida
int r[6] = {0,0,1,1,1,0};

//variables globales
//patrones de error posibles
int e[8][6]={
    {0,0,0,0,0,0},
    {0,0,0,0,0,1},
    {0,0,0,0,1,0},
    {0,0,0,1,0,0},
    {0,0,1,0,0,0},
    {0,1,0,0,0,0},
    {1,0,0,0,0,0},
    {0,0,0,0,1,1} 
};
//H transpuesta
int HT[6][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {1,1,1},
    {1,0,1},
    {1,1,0},
};
//sindromes posibles
int sindromes[8][3] = {
    {0,0,0},
    {1,1,0},
    {1,0,1},
    {1,1,1},
    {0,0,1},
    {0,1,0},
    {1,0,0},
    {0,1,1},
};
//sindrome resultante
int s[3] = {0,0,0};
//mensaje original
int m[6] = {0,0,0,0,0,0};

//funcion para efectuar la suma mod2 de la palabra recibida r con su patron de error correspondiente 
void mensajeOriginal(int i){
    for(int k=0;k<6;k++){
        if(e[i][k]!=0){
            if(r[k]==0)
                m[k] = 1;
            else
                m[k] = 0;
        }
        else
            m[k] = r[k];
    }
}

int main(){
    
    //array auxiliar
    int aux[3] = {0,0,0};

    //producto entre el mensaje recibido r y HT
    for(int j=0;j<3;j++){
        for(int i=0;i<6;i++){
            aux[j] += r[i]*HT[i][j]; 
        }
    }

    //resultado
    cout << aux [0] << aux [1] << aux [2] << "\n";
    
    //mod2 para el sindrome resultante
    for(int i=0;i<3;i++){
        if(aux[i]%2 == 0)
            s[i]=0;
        else
            s[i]=1;
    }

    //sindrome resultante
    cout << "Sindrome:\n";
    cout << s[0] << s[1] << s[2] << "\n";

    //encontrar el patron de error segun su sindrome
    if(s[0]==0 && s[1]==0 && s[2]==0)
        mensajeOriginal(0);
    else if(s[0]==1 && s[1]==1 && s[2]==0)
        mensajeOriginal(1);
    else if(s[0]==1 && s[1]==0 && s[2]==1)
        mensajeOriginal(2);
    else if(s[0]==1 && s[1]==1 && s[2]==1)
        mensajeOriginal(3);
    else if(s[0]==0 && s[1]==0 && s[2]==1)
        mensajeOriginal(4);
    else if(s[0]==0 && s[1]==1 && s[2]==0)
        mensajeOriginal(5);
    else if(s[0]==1 && s[1]==0 && s[2]==0)
        mensajeOriginal(6);
    else if(s[0]==0 && s[1]==1 && s[2]==1)
        mensajeOriginal(7);
    
    //palabra original
    cout << "Mensaje original:\n";
    cout << m[0] << m[1] << m[2] << m[3] << m[4] << m[5] << "\n";
}
