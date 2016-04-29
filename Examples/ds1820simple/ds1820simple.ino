
#include "D:\Code\HAS\Arduino\Libraries\Sensor\OneWire\OneWire.h"
#include "D:\Code\HAS\Arduino\Libraries\Sensor\OneWire\OneWire.cpp"
#include "D:\Code\HAS\Arduino\Libraries\Sensor\Temperature\DS1820S\DallasTemperature.h"
#include "D:\Code\HAS\Arduino\Libraries\Sensor\Temperature\DS1820S\DallasTemperature.cpp"
// ************** ONE WIRE Ds1820
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
 
void setupDS1820() {
  // Start up the library
  sensors.begin();
}
void readDS1820() {
  Serial.println("*********** DS1820 *********");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print("Temp C: ");
  Serial.println(sensors.getTempCByIndex(0)); 
 
}
 
void setup(void) {
  // start serial port
  Serial.begin(9600);
 
  //init DS1820
  setupDS1820();
}
 
void loop(void) { 
  readDS1820();
  delay(3000);  
}
