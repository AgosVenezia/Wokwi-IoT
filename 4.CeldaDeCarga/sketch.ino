//Incluyo librería.
#include <HX711.h>

//Creo el objeto.
HX711 sensorPeso;

//Pines.
const int sensor_dt = 2;
const int sensor_sck = 4;

//Variable para almacenar el peso.
float peso;

void setup() {

  Serial.begin(115200);

  //Inicializo el sensor.
  sensorPeso.begin(sensor_dt, sensor_sck);

}

void loop() {

    //Si el sensor está listo para realizar la lectura, realiza
    //la lectura con sensorPeso.read().
    if (sensorPeso.is_ready()) {

    long lectura = sensorPeso.read();

    //Aplico factor de escala.
    peso = lectura*(50.0/21000.0);

    Serial.print("Peso: ");
    Serial.print(peso);
    Serial.println(" kg");

  }

  delay(2000);

}