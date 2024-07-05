#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Create an instance of the DHT sensor
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int mq135_pin = A0;
const int buzzer_pin = D6;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(mq135_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print ESP8266 local IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route for root / page
  server.on("/", HTTP_GET, handleRoot);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float air_quality = analogRead(mq135_pin);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality: ");
  Serial.println(air_quality);

  // Control the buzzer based on air quality
  if (air_quality > 500) {
    digitalWrite(buzzer_pin, HIGH);
  } else {
    digitalWrite(buzzer_pin, LOW);
  }

  delay(2000); // Adjust delay as needed
}

// Handle root / page request
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP8266 Air Monitoring System</h1>";
  html += "<p>Temperature: " + String(dht.readTemperature()) + " &deg;C</p>";
  html += "<p>Humidity: " + String(dht.readHumidity()) + " %</p>";
  html += "<p>Air Quality: " + String(analogRead(mq135_pin)) + "</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}
