// Datos del dispositivo creado en Blynk
#define BLYNK_TEMPLATE_ID "TMPL2I5-oJLC0"
#define BLYNK_TEMPLATE_NAME "GreenNexus"
#define BLYNK_AUTH_TOKEN "uEAhlnw8zqWDYR58p9NQd16mXigrNRov"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTTYPE DHT11
#define DHTPIN 27          
#define LDR_PIN 34

// Informacion de la red a la que se conectara la app
char ssid[] = "JIRARD";
char pass[] = "Gerardo08";

const int sensorpin = 32;
int sensorvalue=0;
int outputvalue=0;

char auth[] = BLYNK_AUTH_TOKEN;
     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Obtencion de los datos del sensor de humedad y temperatura
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Se envian los datos del sensor dht a los pin virtuales de Blynk
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

  // Se obtiene el valor del sensor de humedad de suelo
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,0,4095,100,0); // Convierte el valor a porcentaje

  delay(1000);

  int sensorValue = analogRead(LDR_PIN); // Lee el valor del LDR (sensor de luminosidad)
  int percentage = map(sensorValue, 0, 4095, 100, 0); // Convierte el valor a porcentaje

  delay(1000);

  // Se envian los datos del sensor de luminosidad y de humedad de suelo a Blynk
  Blynk.virtualWrite(V2,percentage);
  Blynk.virtualWrite(V3,outputvalue);
  Blynk.run();
}