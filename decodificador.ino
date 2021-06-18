#include <Wire.h>

//leds encargados de mostrar el mensaje recibido
#define M1 D3
#define M2 D4
#define M3 D5

//leds encargados de mostrar el sindrome recibido
#define S1 D6
#define S2 D7
#define S3 D8

//configuracion del nodemcu
void setup() {
    
    Serial.begin(9600);
    Wire.begin(D1, D2); 

    //leds del mensaje 
    pinMode(M1,OUTPUT);
    pinMode(M2,OUTPUT);
    pinMode(M3,OUTPUT);

    //leds para el sindrome
    pinMode(S1,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
}

//palabra recibida
int r[6] = {0,0,0,0,0,0};

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

void loop() {
    //variable auxiliar
    int i=0;
    //array auxiliar
    int aux[3] = {0,0,0};

    //guardar la palabra recibida
    Wire.requestFrom(8, 6);
    while(Wire.available()){
        char c = Wire.read();
        r[i] = String(c).toInt();
        i++;
    }

    //imprimir la palabra recibida
    Serial.println("Palabra recibida:");
    Serial.print(r[0]); Serial.print("\t");
    Serial.print(r[1]); Serial.print("\t");
    Serial.print(r[2]); Serial.print("\t");
    Serial.print(r[3]); Serial.print("\t");
    Serial.print(r[4]); Serial.print("\t");
    Serial.print(r[5]); Serial.print("\n");
    
    //producto entre el mensaje recibido r y HT
    for(int j=0;j<3;j++){
        for(int i=0;i<6;i++){
            aux[j] += r[i]*HT[i][j]; 
        }
    }
    //mod2 para el sindrome resultante
    for(int i=0;i<3;i++){
        if(aux[i]%2 == 0)
            s[i]=0;
        else
            s[i]=1;
    }
    
    //imprimir el Sindrome resultante
    Serial.println("Sindrome:");
    Serial.print(s[0]); Serial.print("\t");
    Serial.print(s[1]); Serial.print("\t");
    Serial.print(s[2]); Serial.print("\n");

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

    //imprimir la palabra original
    Serial.println("Palabra original:");
    Serial.print(m[0]); Serial.print("\t");
    Serial.print(m[1]); Serial.print("\t");
    Serial.print(m[2]); Serial.print("\t");
    Serial.print(m[3]); Serial.print("\t");
    Serial.print(m[4]); Serial.print("\t");
    Serial.print(m[5]); Serial.print("\n");

    //mostrar el sindrome en los leds
    sindromeLeds();
    //mostrar el mensaje en los leds
    mensajeLeds();
    //tiempo de espera en busqueda de la nueva palabra
    delay(10000);
}

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

//funcion para mostrar el sindrome en leds
void sindromeLeds(){  
    //led mas significativo
    if(s[0]==1)
        digitalWrite(S3,HIGH);
    else
        digitalWrite(S3,LOW);
    
    //led
    if(s[1]==1)
        digitalWrite(S2,HIGH);
    else
        digitalWrite(S2,LOW);
    
    //led menos significativo
    if(s[2]==1)
        digitalWrite(S1,HIGH);
    else
        digitalWrite(S1,LOW);
}

//funcion para mostrar el mensaje en leds
void mensajeLeds(){
    //led mas significativo
    if(m[3]==1)
        digitalWrite(M3,HIGH);
    else
        digitalWrite(M3,LOW);
    //led
    if(m[4]==1)
        digitalWrite(M2,HIGH);
    else
        digitalWrite(M2,LOW);
    //led menos significativo
    if(m[5]==1)
        digitalWrite(M1,HIGH);
    else
        digitalWrite(M1,LOW);
}