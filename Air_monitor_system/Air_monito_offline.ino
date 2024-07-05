#include <DHT.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int mq135_pin = A0;
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* thingSpeakApiKey = "YourThingSpeakAPIKey";
const int channelNumber = YourThingSpeakChannelNumber;

WiFiClient client;

const int buzzer_pin = D6;
const float temperature_threshold = 30.0; // Example temperature threshold in °C
const int air_quality_threshold = 500; // Example air quality threshold (adjust as needed)

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  int air_quality = analogRead(mq135_pin);
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality: ");
  Serial.println(air_quality);

  // Example: Activate buzzer if temperature exceeds threshold
  if (temperature > temperature_threshold) {
    digitalWrite(buzzer_pin, HIGH);
    delay(1000);
    digitalWrite(buzzer_pin, LOW);
  }

  // Example: Activate buzzer if air quality exceeds threshold
  if (air_quality > air_quality_threshold) {
    digitalWrite(buzzer_pin, HIGH);
    delay(1000);
    digitalWrite(buzzer_pin, LOW);
  }

  if (WiFi.status() == WL_CONNECTED) {
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, air_quality);

    int statusCode = ThingSpeak.writeFields(channelNumber, thingSpeakApiKey);
    if (statusCode == 200) {
      Serial.println("Data sent to ThingSpeak successfully.");
    } else {
      Serial.println("Failed to send data to ThingSpeak. Retry in 15 seconds...");
      delay(15000);
    }
  } else {
    Serial.println("WiFi not connected. Retry in 15 seconds...");
    delay(15000);
    WiFi.begin(ssid, password);
  }

  delay(20000); // Send data every 20 seconds (adjust as needed)
}