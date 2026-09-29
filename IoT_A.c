#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define red D1
#define led D0
float f;
const char* ssid = "Nokia"; // wifi ssid
const char* password = "11111111"; // wifi password
const char* mqttServer = "192.168.88.230"; // IP adress Raspberry Pi
const int mqttPort = 1883;
const char* mqttUser = ""; // if you don't have MQTT Username, no need input
const char* mqttPassword = ""; // if you don't have MQTT Password, no need input
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
pinMode(red,OUTPUT);
Serial.begin(115200);
Serial.println("Connecting to WiFi..");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.println("..");
}
Serial.println("Connected to the WiFi network");
Serial.println();
Serial.println("Connecting to MQTT...");
client.setServer(mqttServer, mqttPort);
client.setCallback(callback);
while (!client.connected()) {
Serial.println("...");
if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
Serial.println("connected");
digitalWrite(led,1);
}
else {Serial.print("failed with state ");
Serial.print(client.state());
delay(2000);
}
}
client.subscribe("esp8266");
}
void callback(char* topic, byte* payload, unsigned int length) {
//Serial.print("Message arrived in topic: ");
// Serial.println(topic);
// Serial.print("Message:");
// Serial.println();
String message = "";
for (int i = 0; i < length; i++) {
// Serial.print((char)payload[i]);
message+=(char)payload[i];
}
f= message.toFloat();
}
void loop() {
client.loop();
Serial.println(f);
 if(f==0){
digitalWrite(D1,0);
}   
 else if(f>0){
digitalWrite(D1,1);
}
else
{
digitalWrite(D1,0);
}}
