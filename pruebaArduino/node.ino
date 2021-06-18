#include <Wire.h>

void setup() {
Serial.begin(9600);
Wire.begin(D1, D2); 
}

int U[6] = {0,0,0,0,0,0};

void loop() {
    int i=0;
    Wire.requestFrom(8, 6);
    while(Wire.available()){
        char c = Wire.read();
        U[i] = String(c).toInt();
        i++;
    }

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
    
    delay(4000);
}