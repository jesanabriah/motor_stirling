# Motor de Stirling

Haciendo uso del aparato U10050  de 3B SCIENTIFIC® PHYSICS, se diseño un dispositivo electronico.
Se usó una placa de Arduino, un sensor BMP180, un potenciometro y un optoacoplador.
Esto permitió medir temperatura, presión, volumen y numeró de vueltas del motor de Stirling.
Un programa en arduino permitió transmitir en forma serial las medidas realizadas sobre el aparato y un programa en Python permitió graficar esta información por medio de un diagrama PV.

En el archivo Fritzing_Sketch.fzz podra encontrar un diagrama esquematico del circuito electrico utilizado, el cual puede ser abierto con el programa Fritzing. Desde allí tambien podra encontrar el archivo PCB correspondiente. Se han usado la libreria que puede encontrar en https://github.com/adafruit/Fritzing-Library para modelar el sensor BMP180.

En el proyecto fue usado el Arduino Mega 2560, sin embargo en general puede servir cualquier Arduino siempre y cuando este tenga las entradas SCL y SDA correspondientes al bus de comunicación serial I2c. Puede encontrar este por ejemplo en Arduino Nano, Arduino Uno, Arduino Mega, etc.

Para la comunicación serial con el computador se ha hecho uso del puerto USB que viene integrado con la placa de Arduino y el sistema se comunica siempre en el primer puerto que encuentra habilitado y conectado. Puede cambiar esto último en el código Python correspondiente.
