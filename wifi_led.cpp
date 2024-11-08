
#include <WiFi.h>
#include <ThingSpeak.h>  // Ensure this library is installed

WiFiClient client;

const char* ssid = "ONLYCSE"; // Your Wi-Fi SSID
const char* password = "keepsmile"; // Your Wi-Fi password

const char* host = "api.thingspeak.com"; // API host
const char* privateKey = "UOZ3XFFHY6J345IO"; // Read API key
const char* privateKey1 = "9HO22G0EY0D8XYD4"; // Write API key

void setup() {
  Serial.begin(115200);
  pinMode(4, OUTPUT);  // Set LED as output

  // Start ThingSpeak client
  ThingSpeak.begin(client);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read the latest value from field 1 of your ThingSpeak channel
  int d = ThingSpeak.readIntField(626082, 1);  // Channel ID and field number

  Serial.print("Field value: ");
  Serial.println(d);

  if (d == 1) {
    digitalWrite(4, HIGH);  // Turn LED ON
    Serial.println("LED ON");
  } else {
    digitalWrite(4, LOW);   // Turn LED OFF
    Serial.println("LED OFF");
  }

  delay(1000); // Delay to avoid hitting the rate limit of ThingSpeak
}



