/*
  Master Lora Node
  The IoT Projects

*/

#include <SPI.h>              // include libraries
#include <LoRa.h>

#define ss 15  //GPIO 15
#define rst 16  //GPIO 16
#define dio0 4  //GPIO 4

byte MasterNode = 0xFF;
byte Node1 = 0xBB;
//byte Node2 = 0xCC;


String SenderNode = "";
String outgoing;
String incoming = "";
 String message = "";

void setup() {
    pinMode(D4,INPUT);
   Serial.begin(115200); 
   while (!Serial);
   Serial.println("LoRa Master Node");

  LoRa.setPins(ss, rst, dio0);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}  

  void loop() {
  if (digitalRead(D4)==1)
  message = "1";
  else
  message = "0";
  sendMessage(message, MasterNode, Node1);
 // onReceive(LoRa.parsePacket());
  
  }

 void sendMessage(String outgoing, byte MasterNode, byte otherNode){
   LoRa.beginPacket();                   // start packet
   LoRa.write(otherNode);              // add destination address
   LoRa.write(MasterNode);            // add sender address
   LoRa.print(outgoing);  
   LoRa.endPacket();                     // finish packet and send it
 }

 void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  if ( sender == 0XBB )
    
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  
  }
