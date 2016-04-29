
#include <pb.h>
#include <ArduinoSerialConnection.h>
#include <MessageRouter.h>
#include <TemperatureParser.h>
#include <DS1820.h>

// Data wire is plugged into port 2 on the Arduino
#define ARDUINO_UUID "FIRSTY"


messaging::IMessageRouter* router;
serial::ISerialConnection* SerialConnection;
messaging::temperature::TemperatureParser* tempParser;
sensor::temperature::DS1820* ds1820;

const unsigned int messageId = 0x03;

void setup(){

  Serial.begin(115200);
  Serial.println("Started connection");

  //Create the serial connection
  SerialConnection = new serial::ArduinoSerialConnection();

  Serial.println("Started router");
  
  //create the message router
  router = new messaging::MessageRouter(SerialConnection);

  Serial.println("Started parser");

  //create the temperature parser
  tempParser = new messaging::temperature::TemperatureParser(ARDUINO_UUID, router);

Serial.println("parser registered");
  //register the parser
  router->registerParser(tempParser);

  Serial.println("Temperature sensor created");
  //Startup the temperature sensor
  const int oneWireBus = 2; //the pin number the data pin is connected to
  ds1820 = new sensor::temperature::DS1820(oneWireBus, "18290923");

Serial.println("sensor registered");
  //register the sensor
  tempParser->registerTemperatureSensor(ds1820);

Serial.println("Sending message (first time)");

  //send a temperature message
  Temperature t = tempParser->MakeTemperatureMessage(ds1820);
  tempParser->sendTemperatureMessage(t);


  
}

void loop(){
  

  //wait for serial reads
  const int arbitraryBufferMaxSize = 512;
  uint8_t* buffer = new uint8_t[arbitraryBufferMaxSize];

  //test loop
  while(true)
  {
    Temperature t = tempParser->MakeTemperatureMessage(ds1820);
    tempParser->sendTemperatureMessage(t);
    delay(1000);
  }

  // end test loop
  
  while(true)
  {
    int bytesRead = SerialConnection->read(buffer, arbitraryBufferMaxSize);
    router->routeMessage(buffer, bytesRead);
  }

  
  
  
}
