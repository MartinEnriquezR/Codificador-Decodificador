#define M1 D3
#define M2 D4
#define M3 D5

#define S1 D6
#define S2 D7
#define S3 D8

void setup(){

    //leds del mensaje 
    pinMode(M1,OUTPUT);
    pinMode(M2,OUTPUT);
    pinMode(M3,OUTPUT);

    //leds para el sindrome
    pinMode(S1,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
}


void loop(){

    //enceder los leds de mensaje
    digitalWrite(M1,HIGH);
    digitalWrite(M2,HIGH);
    digitalWrite(M3,HIGH);
    //encender los leds del sindrome
    digitalWrite(S1,HIGH);
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
}