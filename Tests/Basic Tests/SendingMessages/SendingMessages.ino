

#include <pb.h>
#include <pb_encode.h>
#include "hasmessages/TemperatureMessage.pb.h"
#include "examples/simple/simple.pb.h"
#include <string.h>


void setup() {
  // make the serial connection setup
  Serial.begin(115200);

}

void loop() {
  // initialize a message

  TemperatureMessage temp;
  temp.temperatureF = 0;
  strcpy(temp.deviceName, "send test device message");

  //loop
  while(1)
  {

    uint8_t buffer[512];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, 512);

    pb_encode(&stream, TemperatureMessage_fields, &temp);

    //Serial.write(buffer);
    delay(5 * 1000);
    
  }


}
