/*
Para poder compilar este archivo es necesario el uso de la 
libreria SFE_BMP180 que puede descargarse desde 
https://github.com/sparkfun/BMP180_Breakout. Esta permite usar 
el sensor de presion BMP180 en arduino.

Conecte un potenciometro al pin A0 del conversor analogo digital
y el sensor BMP180 a los pines SCL y SDA del arduino.

La salida es serial por el puerto USB es de la forma:

P:V:T

Es decir, presion, volumen, temperatura, donde la presion es la
presion absoluta, el volumen es realmente un numero entre 0 y 1023
y la temperatura es en grados centigrados.

Tener cuidado si el sensor BMP180 soporta alimentacion o no de 5V, 
si el sensor no soporta 5V se debe conectar a 3.3V en el arduino,
sino puede sufrir daños irreparables.
*/

#include <SFE_BMP180.h>
#include <Wire.h>

//Declaracion de variables
SFE_BMP180 pressure;
char status;
double T, P;

void setup(){
  //Inicializando la comunicacion serial
  Serial.begin(115200);
  //Inicializando el sensor BMP180
  pressure.begin();
}

void loop(){
  //Le ordena al sensor leer la temperatura
  status = pressure.startTemperature();
  
  //Si todo anda bien, espera un tiempo y lee la temperatura
  if (status != 0){
    delay(status);
    status = pressure.getTemperature(T);
    
    /*
    * Si todo va bien ordena al sensor leer la presion.
    * 0-3: Donde 0 es la opcion mas rapida y 3 la de mejor calidad
    */
    if (status != 0){
      status = pressure.startPressure(0);
      
      /*
      * Si todo va bien espera y lee la presion,
      * ajustando el resultado segun la temperatura ambiente
      */
      if (status != 0){
        delay(status);
        status = pressure.getPressure(P, T);
        
        //Si todo va bien envia la informacion serial
        if (status != 0){
          //Envia la informacion Serial como: "P:V:T\n"
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
