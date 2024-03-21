#define BLYNK_TEMPLATE_ID "TMPL2TeM0uCdj"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "wX4ItHtmiE9AtcvA2mSql-P4tfHvu7yn"

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <HX711.h>

HX711 sensorTornillos;
HX711 sensorClavos;
HX711 sensorArandelas;

char network[]="Wokwi-GUEST";
char password[]="";

// Pines
const int sensor_dt_tornillos = 23;
const int sensor_sck_tornillos = 22;
const int sensor_dt_clavos = 4;
const int sensor_sck_clavos = 0;
const int sensor_dt_arandelas = 2;
const int sensor_sck_arandelas = 15;

// Variables para almacenar los pesos
float peso_tornillos;
float peso_clavos;
float peso_arandelas;

// Variables para el stock
int stock_tornillos;
int stock_clavos;
int stock_arandelas;

// Variables para el buzzer
int pin_buzzer = 12;
bool alarma_activada = false;

BlynkTimer timer;


void setup() {

  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN,network,password);

  // Inicializar las celdas de carga
  sensorTornillos.begin(sensor_dt_tornillos, sensor_sck_tornillos);
  sensorClavos.begin(sensor_dt_clavos, sensor_sck_clavos);
  sensorArandelas.begin(sensor_dt_arandelas, sensor_sck_arandelas);

  // Inicializar el buzzer
  pinMode(pin_buzzer, OUTPUT);
  timer.setInterval(500L, controlarAlarma); 

}

void loop() {

  Blynk.run();
  timer.run();

  Blynk.virtualWrite(V0, stock_tornillos);
  Blynk.virtualWrite(V1, stock_clavos);
  Blynk.virtualWrite(V2, stock_arandelas);

  // Leer los pesos
  if (sensorTornillos.is_ready()) {

    long lectura = sensorTornillos.read();
    peso_tornillos = lectura*(50.0/21000.0);
    stock_tornillos = peso_tornillos / 0.01;

    Serial.print("Peso de tornillos: ");
    Serial.print(peso_tornillos);
    Serial.println(" kg.");
    Serial.print("Stock de tornillos: ");
    Serial.print(stock_tornillos);
    Serial.println(".");

  }
  if (sensorClavos.is_ready()) {

    long lectura = sensorClavos.read();
    peso_clavos = lectura*(50.0/21000.0);
    stock_clavos = peso_clavos / 0.005;

    Serial.print("Peso de clavos: ");
    Serial.print(peso_clavos);
    Serial.println(" kg.");
    Serial.print("Stock de clavos: ");
    Serial.print(stock_clavos);
    Serial.println(".");

  }
  if (sensorArandelas.is_ready()) {

    long lectura = sensorArandelas.read();
    peso_arandelas = lectura*(50.0/21000.0);
    stock_arandelas = peso_arandelas / 0.002;

    Serial.print("Peso de arandelas: ");
    Serial.print(peso_arandelas);
    Serial.println(" kg.");
    Serial.print("Stock de arandelas: ");
    Serial.print(stock_arandelas);
    Serial.println(".");

  }

  delay(2000);

}

void controlarAlarma() {
  if ((stock_tornillos <= 100 || stock_clavos <= 200 || stock_arandelas <= 500) && alarma_activada) {
    tone(pin_buzzer, 800);
    Serial.println("¡Stock mínimo!");
  } else {
    noTone(pin_buzzer);
    Serial.println("¡Stock controlado!");
  }

  Serial.println("----------------");

}

BLYNK_WRITE(V3) {
  int estadoAlarma = param.asInt();
  alarma_activada = (estadoAlarma == 1);
}
