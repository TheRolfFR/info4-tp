#include <SPI.h> // The LoRa module includes an interface with SPI bus
#include <RH_RF95.h> // Radiohead Library for LoRa communications
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

RH_RF95 rf95(RFM95_CS, RFM95_INT);

String message;
uint8_t buf[255];
uint32_t i;
uint8_t len = sizeof(buf);
void setup() {
  Serial.begin(115200);
  rf95.init();
  rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);// Bandwidth=125kHz Code rate 4/5 Spreading factor =2^7  
  rf95.setFrequency(868.1); // 868.1, 868.2 or 868.3
  rf95.setTxPower(13, false); // +13dBm
}

void loop() {
  message="LO53 Practice #";
  message+=i;
  i++;
  message.toCharArray((char*)buf, message.length()+1);
  buf[message.length()+1] = 0;
  rf95.send((uint8_t *)buf, message.length()+2);
  rf95.waitPacketSent();
  Serial.print("Sent Message:");
  Serial.println(message);
  delay(2000);
}