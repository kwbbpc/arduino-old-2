
#include <SensorFactory.h>
#include <NanoPbEncoderFactory.h>
#include <MessageRouter.h>
#include <Parser.h>
#include <MessageBuffer.h>
#include <pb.h>
#include <TemperatureEncoder.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TemperatureMessage.pb.h>
#include <hasmessage.pb.h>
#include <DS1820.h>
#include <TimerBucket.h>


static const int Ds1820SPinNumber = 3;

util::TimerBucket* bucket;
messaging::IMessageRouter* messageRouter;
messaging::Parser* parser;

sensor::SensorFactory* sensorFactory;


//writes serialized data to the serial port.
void WriteToSerial(uint8_t* buffer, size_t numberOfBytes)
{
	Serial.print("Writing data to serial: "); Serial.println(numberOfBytes);
	Serial.write(buffer, numberOfBytes);
}

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup");
	sensorFactory = new sensor::SensorFactory(new encoders::nanopb::NanoPbEncoderFactory(&WriteToSerial));
	bucket = util::TimerBucket::getInstance();
	messageRouter = new messaging::MessageRouter();
	Serial.println("Creating message router");
	parser = new messaging::Parser(messageRouter, "C4B25B59-F8FC-4DBD-B2A9-912E20A41367");
	Serial.println("making sensor factory");
	sensor::ISensor* ds1820sPin3 = sensorFactory->CreateDs1820(Ds1820SPinNumber, 2000,"A5A7B1B4-CEF6-4BAF-9412-07BAB120D594");

	Serial.println("Registering sensor");
	messageRouter->registerSensor(ds1820sPin3);
}

void loop()
{
	//If there's serial data to be read, read it in and route the message
	if(Serial.available() > 0)
	{
		uint8_t buffer[512];
		uint8_t bytesRead = 0;
		//read data off the serial port
		while(Serial.available() > 0)
		{
			buffer[bytesRead] = Serial.read();
			++bytesRead;
		}
		parser->parse(buffer, bytesRead);
	}

	if(bucket->isDataAvailable())
	{
		Serial.println("Data is available");
		//retrieve the data and print over serial
		sensor::ISensor* availableData = bucket->getAvailableData();
		if(availableData)
		{
			availableData->sendUpdate();
		}
		
	}
	
}
