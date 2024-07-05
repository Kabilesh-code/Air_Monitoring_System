#include <DHT.h>
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int mq135_pin = A0;
const int buzzer_pin = D6;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(mq135_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  float air_quality = analogRead(mq135_pin);
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality: ");
  Serial.println(air_quality);

  if (air_quality > 500) {
    digitalWrite(buzzer_pin, HIGH);
    delay(1000);
    digitalWrite(buzzer_pin, LOW);
    delay(1000);
  }

  delay(2000); // Adjust delay as needed
}