
#include <ISensorEncoder.h>
#include <IEncoderFactory.h>
#include <SensorFactory.h>
#include <DS1820.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NanoPbEncoderFactory.h>
#include <SensorType.h>
#include <ISensor.h>
#include <ITemperatureSensor.h>
#include <TemperatureEncoder.h>
#include <TemperatureMessage.pb.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <stdio.h>
#include <MsTimer2.h>
#include <TimerBucket.h>
#include <MessageBuffer.h>



static void OnNewData(uint8_t* dataToWrite, size_t length)
{
	TemperatureMessage msg;
	pb_istream_t stream = pb_istream_from_buffer(dataToWrite, length);
	bool status = pb_decode(&stream, TemperatureMessage_fields, &msg);
			
	if(!status)
	{
		log("Error Decoding data");
	}
	else
	{

		//must use a queue here to print items to serial, as this ISR takes too long and it crashes.
		Serial.print("Device ");
		Serial.print(msg.deviceName);
		Serial.print(" (");
		Serial.print(msg.deviceGuid);
		Serial.print(") Reporting: ");
		Serial.print(msg.temperatureF);
		Serial.println(" F");    
	}

		
}


sensor::ISensor* sensorList[16];
int sensorIndex = 0;
sensor::SensorFactory* factory;


void setup()
{
  Serial.begin(115200);

  //Setup the sensor factory
  log("Setup");
  delay(500);
  encoders::IEncoderFactory* encoderFactory = new encoders::nanopb::NanoPbEncoderFactory(&OnNewData);
  log("encoder factory built.");
  factory = new sensor::SensorFactory(encoderFactory);
  
  log("Facotry setup complete");
  
  //create the sensors
  const static int Ds1820SPinNumber = 2;
  const static int Ds1820SUpdateIntervalMs = 1000;
  sensor::ISensor* pTempSensor = factory->CreateDs1820(Ds1820SPinNumber, Ds1820SUpdateIntervalMs, "HHA");
  log("Created sensor...");
	util::TimerBucket* bucket = util::TimerBucket::getInstance();
  
  if(pTempSensor)
  {
    sensorList[sensorIndex] = pTempSensor;
    ++sensorIndex;
	bucket->add(500, pTempSensor, true);
	bucket->add(3500, pTempSensor, true);
	bucket->add(3900, pTempSensor, true);
	bucket->add(2000, pTempSensor, true);
	bucket->add(2000, pTempSensor, true);
	bucket->add(1000, pTempSensor, true);
	bucket->add(2000, pTempSensor, true);
	bucket->add(4000, pTempSensor, true);
	bucket->add(8000, pTempSensor, true);
	bucket->add(8000, pTempSensor, true);
	bucket->add(16000, pTempSensor, true);
	bucket->add(32000, pTempSensor, true);
	log("Added sensor to the timer bucket");
  }
  else
  {
	  log("Error!");
  }

  log("Starting the timer!");
  bucket->start();
    
  
}

void loop()
{
	util::TimerBucket* bucket = util::TimerBucket::getInstance();
	while(bucket->isDataAvailable())
	{			
			Serial.println("Got data.");
			
			sensor::ISensor* sensor = bucket->getAvailableData();
			sensor->sendUpdate();
			
			
	}

}

void log(char* msg)
{
    Serial.println(msg);
 
}


