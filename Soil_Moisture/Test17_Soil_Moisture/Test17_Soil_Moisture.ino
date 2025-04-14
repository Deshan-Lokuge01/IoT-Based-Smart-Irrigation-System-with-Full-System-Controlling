#include <ModbusMaster.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

// WiFi credentials
#define WIFI_AP "NONE"//"Lb"
#define WIFI_PASS "reno0302"//"SLT#54321"

// ThingsBoard credentials
#define TOKEN "Ev9MRc5X4CZRudCVOseu"
#define MQTT_SERVER "thingsboard.cloud"
#define MQTT_PORT 1883

// Modbus settings
#define MAX485_DE 17 // DE
#define MAX485_RE 5  // RE
#define MODBUS_RX_PIN 18 // R0
#define MODBUS_TX_PIN 19 // D1
#define MODBUS_SERIAL_BAUD 4800

constexpr int MAX_VALUES = 10;
int values[MAX_VALUES] = {0}; // Initialize all values to 0
int currentIndex  = 0;
int sum = 0;

ModbusMaster node; // Initialize Modbus and MQTT
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200); // Initialize serial communication
 
  pinMode(MAX485_RE, OUTPUT); // Initialize control pins for MAX485
  pinMode(MAX485_DE, OUTPUT);

  digitalWrite(MAX485_RE, LOW); // Start with the receiver enabled
  digitalWrite(MAX485_DE, LOW);

  // Initialize Modbus communication
  Serial2.begin(MODBUS_SERIAL_BAUD, SERIAL_8N1, MODBUS_RX_PIN, MODBUS_TX_PIN);
  Serial2.setTimeout(200);

  node.begin(1, Serial2);  // Modbus slave ID 1

  node.preTransmission(modbusPreTransmission);  // Callbacks for Modbus communication
  node.postTransmission(modbusPostTransmission);

  WiFi.begin(WIFI_AP, WIFI_PASS);  // Initialize WiFi and MQTT
  InitWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void modbusPreTransmission() {
  delay(500);
  digitalWrite(MAX485_RE, HIGH);
  digitalWrite(MAX485_DE, HIGH);
}

void modbusPostTransmission() {
  digitalWrite(MAX485_RE, LOW);
  digitalWrite(MAX485_DE, LOW);
  delay(500);
}

void InitWiFi() {
  Serial.println("Connecting to AP ...");
  WiFi.begin(WIFI_AP, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  while (!client.connected()) {
    int status = WiFi.status();
    if (status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASS);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    if (client.connect("5428cc90-47d9-11ef-af43-61b559981b3b", TOKEN, NULL)) {
      Serial.println("[DONE]");
    } else {
      Serial.print("[FAILED] [ rc = ");
      Serial.print(client.state());
      Serial.println(" : retrying in 5 seconds]");
      delay(5000);
    }
  }
}

void publish_readings(float soilSensor, float averageSoilSensor) {
  DynamicJsonDocument json(256);
  json["soilSensor"] = soilSensor; // Individual soil moisture reading
  json["averageSoilSensor"] = averageSoilSensor; // Average soil moisture reading
  String strPayload;
  serializeJson(json, strPayload);

  // Publish the JSON string to ThingsBoard telemetry
  client.publish("v1/devices/me/telemetry", strPayload.c_str());
  // Publish the JSON string to ThingsBoard attributes
  client.publish("v1/devices/me/attributes", strPayload.c_str());

  Serial.println("Telemetry and Attributes: " + strPayload);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  uint8_t result;
  uint16_t data[1];
  float soilSensor;

  result = node.readHoldingRegisters(0x0000, 1); // Reading soil moisture value from register 0x0000
  if (result == node.ku8MBSuccess) {
    Serial.println("Success, Received data:");

    data[0] = node.getResponseBuffer(0x00);

    soilSensor = data[0] / 10.0; // Convert to float value by dividing by 10
    int soilValue = data[0] / 10; 

    sum -= values[currentIndex];          // Subtract the oldest value from the sum
    values[currentIndex] = soilValue;     // Replace it with the new value
    sum += soilValue;              // Add the new value to the sum
    currentIndex = (currentIndex + 1) % MAX_VALUES;  // Move to the next index

    float avgSoilValue = (float)sum / MAX_VALUES;      // Calculate the average of the last 10 values
      
    StaticJsonDocument<200> doc;      // Create a JSON document
    doc["soilSensor"] = avgSoilValue;
    doc["soilSensorval"] = soilSensor;

    char buffer[256];// Serialize the JSON document to a string
    size_t n = serializeJson(doc, buffer);

    client.publish("v1/devices/me/telemetry", buffer, n); // Publish the JSON string to ThingsBoard

    Serial.println(buffer);// Print the JSON string to the Serial Monitor
  
  } else {
    Serial.print("Failed, Response Code: ");
    Serial.print(result, HEX);
    Serial.println("");
    Serial.println("Check wiring and device address.");
  }
    
  delay(1000);
}
