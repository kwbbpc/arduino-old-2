
#include <stdio.h>
int lightData = 0;
int blindsData = 0;
int lightSwitchData = 0;
int temperatureData = 0;
int webcamData = 0;
int gasData = 0;
int humidityData = 0;

unsigned int lightId = 0x10;
unsigned int temperatureId= 0x00;
unsigned int thermostatId= 0x01;
unsigned int lightSwitchId = 0x20;
unsigned int blindsId = 0x30;
unsigned int webcamId = 0x31;
unsigned int gasId = 0x40;
unsigned int humidityId = 0x50;


const char signature[] = "HASMESSAGE";
const unsigned int cc2500Id = 0x08;
const int sensorId = 1;

const unsigned int messageId = 0x03;

void setup(){
  Serial.begin(9600);
}

void loop(){
  
  char buffer[200];
  //Temerpature Status
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, temperatureId, temperatureData);
  Serial.println(buffer);
  delay(1000);
  
   sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, thermostatId, thermostatId);
  Serial.println(buffer);
  delay(1000);
  
  //Light 
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, lightId, lightData);
  Serial.println(buffer);
  delay(1000);
  
  //SSR (Light Switch Status
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, lightSwitchId, lightSwitchData);
  Serial.println(buffer);
  delay(1000);
  
  //Servo (Blinds) Status
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, blindsId, blindsData);
  Serial.println(buffer);
  delay(1000);
  
  
  //Servo (Webcam) Status
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, webcamId, webcamData);
  Serial.println(buffer);
  delay(1000);
  
  //Gas (status)
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, gasId, gasData);
  Serial.println(buffer);
  delay(1000);

  //Humidity status
  sprintf(buffer, "%s,%d,%d,%d,%d", signature, messageId, cc2500Id, humidityData, humidityData);
  Serial.println(buffer);
  
  delay(1000);
}
