

#include <SensorFactory.h>
#include <ISensor.h>
#include "../HasTemperature/DS1820.h"
#include "../encoders/IEncoderFactory.h"

namespace sensor{

	SensorFactory::SensorFactory(encoders::IEncoderFactory* encoderFactory)
		: m_encoderFactory(encoderFactory)
	{
		
	}

	
	ISensor* SensorFactory::CreateDs1820(int pinNumber, int updateTimerIntervalMs, const char* guid)
	{
		m_encoderFactory->makeTemperatureEncoder();
		ISensor* sensor = new temperature::DS1820(pinNumber, m_encoderFactory->makeTemperatureEncoder(), updateTimerIntervalMs, guid);

		bool success = sensor->initialize();
		if(success)
		{
			return sensor;
		}
		else
		{
			delete sensor;
			//TODO: Log an error here
			Serial.write("Error when attempting to create sensor");

			return 0;
		}
	}
}