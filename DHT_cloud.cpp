#include <WiFi.h>
#include <DHT.h>
#include "ThingSpeak.h"

#define DHTPIN 4             // Pin connected to DHT sensor
#define DHTTYPE DHT11        // DHT sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE);    // Initialize DHT sensor
WiFiClient client;           // Initialize WiFi client

// WiFi and ThingSpeak credentials
const char* ssid = "Praveen";                 // WiFi SSID
const char* password = "123456789";           // WiFi password
unsigned long channelID = 539141;             // ThingSpeak Channel ID
const char* writeAPIKey = "0SY6SUIDJ47NLIXN"; // ThingSpeak Write API Key

float humidity, temperature;

void setup() {
    Serial.begin(115200);
    dht.begin();  // Start DHT sensor

    // Connect to WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
    // Read humidity and temperature from the DHT sensor
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Display readings in Serial Monitor
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);

    // Upload data to ThingSpeak
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    int writeSuccess = ThingSpeak.writeFields(channelID, writeAPIKey);

    if (writeSuccess == 200) {
        Serial.println("Data successfully uploaded.");
    } else {
        Serial.println("Failed to upload data. Error code: " + String(writeSuccess));
    }

    delay(10000); // Delay before next upload (ThingSpeak limits to 15 sec updates)
}
