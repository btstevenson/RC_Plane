#include <SoftwareSerial.h>

#define RX 2
#define TX 3

SoftwareSerial wifly(RX, TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifly.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(wifly.available())
  {
    Serial.write(wifly.read());
  }
  if(Serial.available())
  {
    wifly.write(Serial.read());
  }

}
