/*    
    Copyright 2018 Jorge Sanabria
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    

    Para poder compilar este archivo es necesario el uso de la 
    libreria SFE_BMP180 que puede descargarse desde 
    https://github.com/sparkfun/BMP180_Breakout. Esta permite usar 
    el sensor de presion BMP180 en arduino.
    
    Conecte un potenciometro al pin A0 del conversor analogo digital
    y el sensor BMP180 a los pines SCL y SDA del arduino.
    
    La salida es serial por el puerto USB y es de la forma: "P:V:T"
    
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

//Para el contador de vueltas
boolean anterior = 0;
boolean actual  = 0;
int m = 0;//Numero de pulsos

void setup(){
  //Inicializando la comunicacion serial
  Serial.begin(115200);
  //Inicializando el sensor BMP180
  pressure.begin();
  //Entrada para el optoacoplador para medir cada vez que da una vuelta
  pinMode(2,INPUT);
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
          //Calcula el numero de pulsos
          actual = digitalRead(2);
          if(actual != anterior){
            //M esta limitado por el maximo valor posible sin que se genere overflow
            m++;
          }
          anterior = actual;
          
          //Envia la informacion Serial como: "P:V:T\n"
          Serial.print(P);
          Serial.print(":");
          Serial.print(analogRead(A0));
          Serial.print(":");
          Serial.print(T);
          Serial.print(":");
          Serial.println(m/2);//Numero de vueltas = pulsos / 2
        }
      }
    }
  }
}
