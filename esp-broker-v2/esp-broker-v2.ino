#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// CONSTANT VARIABLES
//***WIFI***
const char* ssid = "Phase";
const char* password =  "12345689**+";

//***SERVER***
const char* mqttServer = "m21.cloudmqtt.com";
const int mqttPort = 14531;
const char* mqttUser = "girlnujd";
const char* mqttPassword = "uzlMkPzoIxcs";

const char clientID = "ESP8266Client";

//***CODE***
char* raw_electric_received;
char* raw_water_received;
uint8_t i = 0;
uint8_t flag = 0;

//***Naming***
#define WATER_LENGTH    5
#define ELECTRIC_LENGTH 5

// Initialize a client
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  //init serial port
  Serial.begin(115200);
 
  //connect to wifi hostpot
  WiFi.begin(ssid, password);
  
  //verify wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  //configure the client instance to be ready for use
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  //verify client's connection to server
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect(clientID, mqttUser, mqttPassword )) // arguments: clientID, username, password
    {
      Serial.println("connected");  
 
    }
    else
    {
      Serial.print("failed with state: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  client.publish("esp/test", "Data tu ESP");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void loop() {
  client.loop();
  
  if(Serial.readBytes())
  {
    Serial.println(Serial.readBytes());
  }
}
