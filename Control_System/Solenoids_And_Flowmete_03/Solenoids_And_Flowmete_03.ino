#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#define WIFI_AP "NONE" // "Lb"
#define WIFI_PASS "reno0302" // "SLT#54321"

#define TOKEN "WmqYfL6H16TpjYihOx8A"
#define MQTT_SERVER "thingsboard.cloud"
#define MQTT_PORT 1883

#define GPIO1 32
#define GPIO2 33
#define GPIO3 14
#define GPIO4 12
#define GPIO1_PIN 1
#define GPIO2_PIN 2
#define GPIO3_PIN 3
#define GPIO4_PIN 4

#define LED_BUILTIN 2
#define SENSOR 13 // flow sensor input pin

constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

boolean gpioState[] = {false, false, false, false};

// Flow meter variables
long currentMillis = 0;
long previousMillis = 0;
int interval = 1;
boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
float totalLitres; // Add this line

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  // Set GPIO pins to OUTPUT and ensure they are off initially
  pinMode(GPIO1, OUTPUT);
  digitalWrite(GPIO1, HIGH);
  pinMode(GPIO2, OUTPUT);
  digitalWrite(GPIO2, HIGH);
  pinMode(GPIO3, OUTPUT);
  digitalWrite(GPIO3, HIGH);
  pinMode(GPIO4, OUTPUT);
  digitalWrite(GPIO4, HIGH);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  totalLitres = 0.0; // Initialize totalLitres
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);   // flow sensor pulse count

  WiFi.begin(WIFI_AP, WIFI_PASS);
  InitWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(on_message);

  // Set initial state of GPIO to be off
  for (int i = 0; i < 4; i++) {
    gpioState[i] = false;
  }

  // Publish initial state to ThingsBoard
  publish_gpio_status_to_thingsboard();
}

void on_message(char* topic, byte* payload, unsigned int length) {
  Serial.println("On message");

  String payloadStr;
  for (unsigned int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }

  Serial.println("setGpioStatus: " + payloadStr);
  Serial.println("Topic: " + String(topic));

  DynamicJsonDocument json(256);
  DeserializationError error = deserializeJson(json, payloadStr);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  String methodName = json["method"].as<String>();

  if (methodName.equals("getGpioStatus1")) {
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    String data = gpioState[0] ? "true" : "false";
    client.publish(responseTopic.c_str(), data.c_str());
  } 
  else if (methodName.equals("getGpioStatus2")) {
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    String data = gpioState[1] ? "true" : "false";
    client.publish(responseTopic.c_str(), data.c_str());
  } 
  else if (methodName.equals("getGpioStatus3")) {
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    String data = gpioState[2] ? "true" : "false";
    client.publish(responseTopic.c_str(), data.c_str());
  }
   else if (methodName.equals("getGpioStatus4")) {
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    String data = gpioState[3] ? "true" : "false";
    client.publish(responseTopic.c_str(), data.c_str());
  } 
  else if (methodName.equals("setGpioStatus")) {
    set_gpio_status(json["params"]["pin"], json["params"]["enabled"]);
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    responseTopic.replace("\"", "");
    Serial.print("Response: ");
    Serial.println(responseTopic);
    String data;

    if (json["params"]["pin"] == 1){
      data = gpioState[0] ? "true" : "false";
      client.publish(responseTopic.c_str(), data.c_str());
    } else if (json["params"]["pin"] == 2){
      data = gpioState[1] ? "true" : "false";
      client.publish(responseTopic.c_str(), data.c_str());
    } else if (json["params"]["pin"] == 3){
      data = gpioState[2] ? "true" : "false";
      client.publish(responseTopic.c_str(), data.c_str());
    } else if (json["params"]["pin"] == 4){
      data = gpioState[3] ? "true" : "false";
      client.publish(responseTopic.c_str(), data.c_str());
    }

    // Publish updated relay statuses as attributes to ThingsBoard
    publish_gpio_status_to_thingsboard();
  }
}

void set_gpio_status(int pin, boolean enabled) {
  if (pin == GPIO1_PIN) {
    digitalWrite(GPIO1, enabled ? LOW : HIGH);
    gpioState[0] = enabled;
  } else if (pin == GPIO2_PIN) {
    digitalWrite(GPIO2, enabled ? LOW : HIGH);
    gpioState[1] = enabled;
  } else if (pin == GPIO3_PIN) {
    digitalWrite(GPIO3, enabled ? LOW : HIGH);
    gpioState[2] = enabled;
  } else if (pin == GPIO4_PIN) {
    digitalWrite(GPIO4, enabled ? LOW : HIGH);
    gpioState[3] = enabled;
  }
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
    if (client.connect("d2877340-fd4f-11ee-8c7f-a31d0e3c99f8", TOKEN, NULL)) {
      Serial.println("[DONE]");
      client.subscribe("v1/devices/me/rpc/request/+");
    } else {
      Serial.print("[FAILED] [ rc = ");
      Serial.print(client.state());
      Serial.println(" : retrying in 5 seconds]");
      delay(5000);
    }
  }
}

void publish_gpio_status_to_thingsboard() {
  DynamicJsonDocument json(256);
  json["GPIO1"] = gpioState[0] ? "true" : "false";
  json["GPIO2"] = gpioState[1] ? "true" : "false";
  json["GPIO3"] = gpioState[2] ? "true" : "false";
  json["GPIO4"] = gpioState[3] ? "true" : "false";
  String strPayload;
  serializeJson(json, strPayload);
  client.publish("v1/devices/me/attributes", strPayload.c_str());
}

void publish_flow_meter_to_thingsboard() { // Flow sensor 
  DynamicJsonDocument json(256);
  json["FlowRate"] = flowRate;
  json["TotalMilliLitres"] = totalMilliLitres;
  String strPayload;
  serializeJson(json, strPayload);
  client.publish("v1/devices/me/attributes", strPayload.c_str());
  client.publish("v1/devices/me/telemetry", strPayload.c_str());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  currentMillis = millis();  // flow sensor calculation begining
  if (currentMillis - previousMillis > interval) {
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    //flowrate = -0.0231*(flowrate^2) + 1.9599*flowrate - 41.458 // calibrated value for flowrate
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    totalLitres = totalMilliLitres / 1000.0;
    

    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));
    Serial.print(" L/min\t");

    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print(" mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println(" L");

    // Publish flow meter data to ThingsBoard
    publish_flow_meter_to_thingsboard();
  }
}

