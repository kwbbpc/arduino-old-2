

#include "TestSensorFactory.h"
#include <Sensor\ISensor.h>
#include <Sensor\test\TestTemperatureSensor.h>
#include <Encoders\IEncoderFactory.h>

namespace sensor{

	TestSensorFactory::TestSensorFactory(encoders::IEncoderFactory* encoderFactory)
		: m_encoderFactory(encoderFactory)
	{
		
	}

	
	ISensor* TestSensorFactory::CreateTestTemperatureSensor()
	{
		m_encoderFactory->makeTemperatureEncoder();
		ISensor* sensor = new temperature::TestTemperatureSensor(m_encoderFactory->makeTemperatureEncoder());

		bool success = sensor->initialize();
		if(success)
		{
			return sensor;
		}
		else
		{
			delete sensor;
			return 0;
		}
	}
}