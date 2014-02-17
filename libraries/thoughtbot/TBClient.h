
/*
 * TBClient.h - Library containing convenience functions for thoughtbot sensor board.
 * Create by Tony DiPasquale, February 11, 2014.
 * Released into the public domain.
 */

#ifndef TBClient_h
#define TBClient_h

#include "Arduino.h"

class TBClient
{
  public:
    TBClient(byte*, int);
    void sendData(byte*, byte*);
};

#endif

