
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>

#include <TBClient.h>
#include <TBWrapper.h>

const String rightDoorID = "SensorID01";
const String leftDoorID = "SensorID02";

TBClient client((byte *) "bath1", 32);

byte leftDoorStatus = 0;
byte rightDoorStatus = 0;

void clientSetup()
{
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
}

void clientLoop()
{
  byte left = digitalRead(2);
  
  if (leftDoorStatus != left) {
    leftDoorStatus = left;
    sendDataWithIDandStatus(leftDoorID, leftDoorStatus);
  }

  byte right = digitalRead(3);
  
  if (rightDoorStatus != right) {
    rightDoorStatus = right;
    sendDataWithIDandStatus(rightDoorID, rightDoorStatus);
  }
}

void sendDataWithIDandStatus(String id, byte status)
{
  byte doorStatus[12];
  id.getBytes(doorStatus, 11);
  doorStatus[11] = status;
  client.sendData((byte *)"tbhub", (byte *)doorStatus);
  free(doorStatus);
}
