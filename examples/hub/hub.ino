#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>

#include <Bridge.h>
#include <Process.h>

void setup()
{
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.setRADDR((byte *) "tbhub");
  Mirf.payload = 32;
  
  Mirf.config();
  
  Bridge.begin();
}

void loop()
{
  if (Mirf.dataReady()) {
    byte data[32];
    Mirf.getData((byte *) &data);
    String id = String((char *)data);
    sendData(id, data[11]);
  }
}

void sendData(String id, byte value)
{
  Process curl;
  curl.begin("curl");
  curl.addParameter("-k");
  curl.addParameter("-X");
  curl.addParameter("POST");
  curl.addParameter("-H");
  curl.addParameter("X-Parse-Application-Id:YOUR-APPLICATION-ID");
  curl.addParameter("-H");
  curl.addParameter("X-Parse-REST-API-Key:YOUR-PARSE-API-KEY");
  curl.addParameter("-H");
  curl.addParameter("Content-Type:application/json");
  curl.addParameter("-d");
  
  String data = "{\"sensor\":{\"__type\":\"Pointer\",\"className\":\"Sensor\",\"objectId\":\"";
  data += id;
  data += "\"},\"value\":";
  data += value;
  data += "}";
  
  curl.addParameter(data);
  curl.addParameter("https://api.parse.com/1/classes/SensorValue");
  curl.run();
}
