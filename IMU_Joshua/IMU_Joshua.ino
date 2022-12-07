#include<Wire.h>
#include<SPI.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055();

void setup() {
  Serial.begin(115200);
    //Check if the IMU is on, and if it is then get initial readings
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  delay(1000);
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  //Serial.print("X: ");
  //Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  //Serial.print("\tZ: ");
  //Serial.print(event.orientation.z, 4);

  Serial.println("");
}
