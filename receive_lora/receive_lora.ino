#include <SPI.h> // The LoRa module includes an interface with SPI bus
#include <RH_RF95.h> // Radiohead Library for LoRa communications
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

RH_RF95 rf95(RFM95_CS, RFM95_INT);

uint8_t buf[255];
uint8_t len = sizeof(buf);
void setup() {
  Serial.begin(115200);
  rf95.init();
  rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);// Bandwidth=125kHz Code rate 4/5 Spreading factor =2^7  
  rf95.setFrequency(868.1); // 868.1, 868.2 or 868.3
}void loop() {
  if (rf95.waitAvailableTimeout(4000)) { // Wait for a packet for 4 seconds
    if (rf95.recv(buf, &len)) {
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.print("SNR: ");
      Serial.println(rf95.lastSNR(), DEC);
    }
  }  else Serial.println("No reception");
}