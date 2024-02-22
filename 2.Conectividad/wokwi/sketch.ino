//Lo que vamos a hacer ahora es configurar todo para acceder al servidor en modo cliente.
//El cliente en este caso será la ESP32 que va a acceder a una base de datos.

//Importamos librería del DHT.
#include "DHT.h" //<DHT.h>

//HTTPClient.h se utiliza para realizar solicitudes HTTP, lo que permite a la ESP32
//comunicarse con servidores web y consumir o enviar datos a través del protocolo HTTP.
#include <HTTPClient.h>
#include <WiFi.h> //Para la conexión WiFi de la placa.

//Definimos el nombre y contraseña de la red WiFi a la que nos vamos a conectar.
const char *ssid = "Wokwi-GUEST";
const char *password = "";

#define DHTTYPE DHT22
#define DHTPIN 15

//Creo un objeto de nombre: dht que va a ser de tipo DHT, como si yo declarara
//un entero por ejemplo. Son comandos específicos de la librería del sensor
//DHT.
DHT dht(DHTPIN, DHTTYPE);

float temperatura;
float humedad;

void setup() {

    //Velocidad de comunicación en bits por segundo. Si se fijan, es una velocidad
    //más rápida que en Arduino.
    Serial.begin(115200);

    //begin() se utiliza para iniciar la comunicación con el sensor y prepararlo
    //para realizar lecturas.
    dht.begin();

    //Con la siguiente línea nos conectamos a la red WiFi.
    WiFi.begin(ssid, password);

    //Mientras no se establezca la conexión, se van a mostrar puntos suspensivos.
    //Y cuando se establezca, va a mostrar el mensaje "Conexión OK" en la consola.
    //!= es "no igual" o negado.
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("Conexión OK!");

}


void loop() {
    //Acá hacemos la lectura del sensor
    temperatura = dht.readTemperature();
    humedad = dht.readHumidity();
    Serial.print("Temperatura actual: ");
    Serial.print(temperatura);
    Serial.println("ºC");
    Serial.print("Humedad actual: ");
    Serial.print(humedad);
    Serial.println("%");
    Serial.println();

    delay(2000);

    //Después de leer los datos de temperatura y humedad del sensor, se va a ejecutar la siguiente
    //función, que básicamente envía los datos al servidor mediante el método POST.
    EnvioDatos();

}

void EnvioDatos() {

      //Lo que está dentro del if se va a ejecutar cuando se esté conectado a la red WiFi.
      if (WiFi.status() == WL_CONNECTED) {

      //Creamos el objeto "http" que invoca las funciones de la librería HTTPClient.
      HTTPClient http;

      //En un String almacenamos el mensaje que va a ser enviado al servidor.
      //Pasamos la variable temperatura y la variable humedad, de Float a String.
      String datos_a_enviar = "temperatura=" + String(temperatura) + "&humedad=" + String(humedad);
      
      //Iniciamos el protocolo HTTP y le indicamos donde está el script PHP donde se van a enviar los datos.
      http.begin("https://agosveneziaiot.000webhostapp.com/EstadoESP.php");
      
      //Con lo siguiente definimos la estructura en la que se van a enviar los datos.
      //Las solicitudes POST generalmente se envían a través de un formulario "form".
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      //Enviamos la solicitud POST.
      //POST y GET son dos métodos utilizados para enviar información.
      //En GET los datos se envían directamente en la URL.
      //En POST la información se envía en el cuerpo de la solicitud, no en la URL. Los datos se envían de manera más discreta.
      http.POST(datos_a_enviar);

      //Con esto obtenemos el mensaje que envía el servidor.
      String cuerpo_respuesta = http.getString();
      Serial.println("El servidor respondió: ");
      Serial.println(cuerpo_respuesta);

      //Finalizamos la petición.
      http.end();
      
      } else {
      Serial.println("Error en la conexión WiFi");
      }
      delay(5000);
}