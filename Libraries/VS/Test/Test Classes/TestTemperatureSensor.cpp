
#include "TestTemperatureSensor.h"

namespace sensor{ namespace temperature{

TestTemperatureSensor::TestTemperatureSensor(encoders::ISensorEncoder* encoder)
	: m_encoder(encoder)
{
}

//performs initialization of the sensor
bool TestTemperatureSensor::initialize()
{
	return true;
}

//tells the sensor to use its encoder and send a new update
void TestTemperatureSensor::sendUpdate()
{

	m_encoder->sendNewMessage(this);

}

//get the sensors unique GUID
char* TestTemperatureSensor::getUniqueId()
{
	return "3D49B360-0FE5-4007-86B6-C1616DB5C842";
}

//gets the sensor type
SensorType::Enum TestTemperatureSensor::getType()
{
	return SensorType::Temperature;
};

float TestTemperatureSensor::getTemperatureC()
{
	return 90.13f;
}
float TestTemperatureSensor::getTemperatureF()
{
	return 200.31f;
}
char* TestTemperatureSensor::getDeviceName()
{
	return "TestSensor - Noname";
}

}}