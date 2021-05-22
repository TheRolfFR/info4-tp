#include <SPI.h> // The LoRa module includes an interface with SPI bus
#include <RH_RF95.h> // Radiohead Library for LoRa communications
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// arduino binary installed on /vm/ 402

RH_RF95 rf95(RFM95_CS, RFM95_INT);

#include <math.h>
#define PI acos(-1.0)

double Lambda = 300000000.0/868100000.0;

double gains(double Distance, double Pr, double Pt) {
    return Pr - Pt - 20* log10(Lambda/(4*PI*Distance));
}

double distance(double GtGr, double Pr, double Pt) {
    return Lambda/(4*PI*pow(10, (Pr-Pt-(GtGr))/20));
}

uint8_t buf[255];
uint8_t len = sizeof(buf);

#define POWER_TRANSMITTER 13 // 13 dBm basé sur la la tx power de base

uint32_t i = 0;
double gr_gt, dis;

void setup() {
  Serial.begin(115200);
  rf95.init();
  rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128);// Bandwidth=125kHz Code rate 4/5 Spreading factor =2^7  
  rf95.setFrequency(868.1); // 868.1, 868.2 or 868.3

  // I need real values for an accurate gr_gt, but the professor didn't gave it to us
  // to calibrate gr_gt, I need to enter a known distance for a given power received
  // I know the 
  gr_gt = gains(1, -91.0, POWER_TRANSMITTER);
  
}void loop() {
  if (rf95.waitAvailableTimeout(4000)) { // Wait for a packet for 4 seconds
    if (rf95.recv(buf, &len)) {
      Serial.print("ID=");
      Serial.print(i++);
      Serial.print(", RSSI=");
      int16_t rssi = rf95.lastRssi();
      Serial.print(rssi, DEC);
      Serial.print(", distance=");
      dis = distance(gr_gt, (double) rssi, (double) POWER_TRANSMITTER);
      Serial.print(dis);
      Serial.println("m");
    }
  }  else Serial.println("No reception");
}
