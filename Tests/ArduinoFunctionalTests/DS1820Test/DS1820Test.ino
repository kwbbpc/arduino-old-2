

#include <DS1820.h>
#include <pb.h>
#include <NanoPbEncoderFactory.h>
#include <hasmessages\TemperatureMessage.pb.h>
#include <SensorFactory.h>
#include <ITemperatureSensor.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <TimerBucket.h>

void WriteUpdate(uint8_t* buffer, size_t numberOfBytes)
{
	Serial.write(buffer, numberOfBytes);

}

static const int Ds1820PinNumber = 3;
sensor::temperature::ITemperatureSensor* tempSensor;

void setup()
{
	Serial.begin(115200);

	encoders::nanopb::NanoPbEncoderFactory* nanoPbEncoderFactory = new encoders::nanopb::NanoPbEncoderFactory(&WriteUpdate);
	sensor::SensorFactory* sensorFactory = new sensor::SensorFactory(nanoPbEncoderFactory);
	tempSensor = new sensor::temperature::DS1820(Ds1820PinNumber, nanoPbEncoderFactory->makeTemperatureEncoder(), 2000, "1AA71A95-8788-4203-942D-F2D75378C665");
	Serial.println("Setup complete.");
}

int count = 0;
void loop()
{

  /* add main program code here */
	count++;
	if(count > 16000)
	{
		Serial.println("sending update.");
		tempSensor->sendUpdate();
		count = 0;
	}

}
