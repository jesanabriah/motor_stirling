#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;
char status;
double T, P;
  
void setup(){
  Serial.begin(115200);
  pressure.begin();
}

void loop(){
  status = pressure.startTemperature();
  
  if (status != 0){
    delay(status);
    status = pressure.getTemperature(T);
    
    if (status != 0){
      //0 - 3: Where 3 is the best and the slowest
      status = pressure.startPressure(0);
      
      if (status != 0){
        delay(status);
        status = pressure.getPressure(P, T);
        
        if (status != 0){
          //Serial: P, V, T 
          Serial.print(P);
          Serial.print(":");
          Serial.print(analogRead(A0));
          Serial.print(":");
          Serial.println(T);
        }
      }
    }
  }
}
