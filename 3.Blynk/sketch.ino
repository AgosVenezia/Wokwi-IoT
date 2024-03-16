//Credenciales que tienen que copiar y pegar desde su
//proyecto en Blynk.
#define BLYNK_TEMPLATE_ID "TMPL2TeM0uCdj"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "zXLGixnvoz5RvjG8N8NS_ebwdU8kv98a"

#define BLYNK_PRINT Serial

//Acuerdense de importar las librerías en "Library Manager".
//La librería de "Blynk" y "DHT sensor library".
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "DHT.h"

//Credenciales para lectura de DHT22
#define pin2 2
DHT dht2(pin2, DHT22);

char network[]="Wokwi-GUEST";
char password[]="";

//Para lectura analógica del LDR
int ldr = 34;

void setup() {
  Serial.begin(115200);
  dht2.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN,network,password);

}

void loop() {

  delay(2000);

  leerdht2();

  Blynk.run();

}

void leerdht2() {

  //Lectura del DHT22
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();

  //Lectura del LDR.
  int Lectura = analogRead(ldr);

  //Envío a Blynk.
  Blynk.virtualWrite(V0, t2);
  Blynk.virtualWrite(V1, h2);
  Blynk.virtualWrite(V3, Lectura);

  Serial.print("Temperatura: ");
  Serial.print(t2);
  Serial.println(" °C.");

  Serial.print("Humedad: ");
  Serial.print(h2);
  Serial.println(" %.");

  Serial.println("----------------");

}


//Función para controlar brillo del LED.
//Recuerden que para activar o desactivar un pin digital
//con un control On/Off no hace falta crear nada, Blynk
//lo hace automáticamente.
BLYNK_WRITE(V2) {

    int pin = param.asInt();

    analogWrite(12, pin);

}