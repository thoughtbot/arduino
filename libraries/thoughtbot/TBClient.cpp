
/*
 * TBClient.cpp - Library containing convenience functions for thoughtbot sensor board.
 * Create by Tony DiPasquale, February 11, 2014.
 * Released into the public domain.
 */

#include "Arduino.h"

// Libraries for wireless communication
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#include "TBClient.h"

TBClient::TBClient(byte *name, int payload)
{
  Mirf.csnPin = 10;
  Mirf.cePin = 9;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR(name);
  Mirf.payload = payload;
  Mirf.config();
}

void TBClient::sendData(byte *address, byte *data)
{
  Mirf.setTADDR(address);
  Mirf.send(data);
  while(Mirf.isSending()) ;
  Mirf.powerDown();
}

