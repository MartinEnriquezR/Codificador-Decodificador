//librerias de Arduino
#include <Wire.h>

//pines de entrada del mensaje
#define M3 7
#define M2 6
#define M1 5
//pines para introducir el error
#define E6 8
#define E5 9
#define E4 10
#define E3 11
#define E2 12
#define E1 13
//pushbutton para la generacion de la palabra
#define GENERAR 2
//led para mostrar el mensaje de forma serial
#define LED 4

//configuracion del arduino
void setup(){

//pines de mensaje
pinMode(M1,INPUT);
pinMode(M2,INPUT);
pinMode(M3,INPUT);

//pines de error
pinMode(E1,INPUT);
pinMode(E2,INPUT);
pinMode(E3,INPUT);
pinMode(E4,INPUT);
pinMode(E5,INPUT);
pinMode(E6,INPUT);

//pushbutton para la genracion de la palabra
attachInterrupt(digitalPinToInterrupt(GENERAR),generarMensaje,RISING);

//pin led encargado de mostrar el mensaje
pinMode(LED,OUTPUT);

//habilitar comunicacion IC2
Wire.begin(8);

//Configuracion para el envio de la palabra codificada
Wire.onRequest(enviar);

//configuracion de la comunicacion serial
Serial.begin(9600);
}

//variables globales
int mensaje[3] = {0,0,0};
int error[6] = {0,0,0,0,0,0};
int U[6] = {0,0,0,0,0,0};
int G[3][6] = {
    {1,1,1,1,0,0},
    {1,0,1,0,1,0},
    {1,1,0,0,0,1},
};

void loop(){
}

//generacion del mensaje teniendo en cuenta el error ingresado
void generarMensaje(){

    //guardar mensaje a enviar
    mensaje[0] = digitalRead(M3);
    mensaje[1] = digitalRead(M2);
    mensaje[2] = digitalRead(M1);

    //guardar los errores introducidos
    error[0] = digitalRead(E1);
    error[1] = digitalRead(E2);
    error[2] = digitalRead(E3);
    error[3] = digitalRead(E4);
    error[4] = digitalRead(E5);
    error[5] = digitalRead(E6);

    //variable auxiliar
    int aux[6] = {0,0,0,0,0,0};

    //producto del vector mensaje por la matriz generadora
    for(int j=0;j<6;j++){
        for(int i=0;i<3;i++){
            aux[j] += mensaje[i]*G[i][j];
        }      
    }

    //representar el resultado en modulo 2
    for(int i=0;i<6;i++){
        if(aux[i]%2 == 0)
            U[i]=0;
        else
            U[i]=1;
    }

    //añadir el error
    for(int i=0;i<6;i++){
        if(error[i]!=0){
            // cambiar el valor de la palabra
            if(U[i]==0)
                U[i]=1;
            else
                U[i]=0;
        }
    }

    //imprimir a enviar en consola
    Serial.print(U[0]);
    Serial.print("\t");
    Serial.print(U[1]);
    Serial.print("\t");
    Serial.print(U[2]);
    Serial.print("\t");
    Serial.print(U[3]);
    Serial.print("\t");
    Serial.print(U[4]);
    Serial.print("\t");
    Serial.print(U[5]);
    Serial.print("\n");
}

//Enviar la palabra codificada
void enviar(){
    for(int i=0;i<6;i++){
        if(U[i]==0)
            Wire.write("0");
        else
            Wire.write("1");
    }
}