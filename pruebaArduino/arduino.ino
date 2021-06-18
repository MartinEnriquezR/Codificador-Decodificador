#include <Wire.h>

void setup() {
Wire.begin(8);                
Wire.onRequest(requestEvent); 
Serial.begin(9600);           
}

//mensaje
int U[6] = {1,1,1,0,1,1}; 

void loop() {
}

void requestEvent() {
  for(int i=0;i<6;i++){
    if(U[i]==0)
      Wire.write("0");
    else
      Wire.write("1");
  }
}