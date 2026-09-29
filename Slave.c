/*
  Lora Node1
  The IoT Projects

*/
#include <SPI.h>              // include libraries
#include <LoRa.h>

#define ss 10
#define rst 9
#define dio0 2

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte MasterNode = 0xFF;
//byte Node1 = 0xBB;

String Mymessage = "";

void setup() {
 //pinMode(A0,INPUT);
  pinMode(D4,OUTPUT);
  LoRa.setPins(ss, rst, dio0);
  Serial.begin(115200);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
 // data = analogRead(A0);  //put Sensor insert into soil
 // sendMessage(Mymessage, MasterNode, Node1);
  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address

  String incoming = "";

  while (LoRa.available()) {
    incoming = (char)LoRa.read();
  }
  int val = incoming.toInt();
  Serial.println(val);
  if (val==1)
  digitalWrite(D4,1);
  else 
  digitalWrite(D4,0); 
  delay(200);
}

void sendMessage(String outgoing, byte MasterNode, byte Node1) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(MasterNode);              // add destination address
  LoRa.write(Node1);             // add sender address
   LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
}
