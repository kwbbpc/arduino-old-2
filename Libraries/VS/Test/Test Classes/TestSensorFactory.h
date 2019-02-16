#ifndef TESTSENSORFACTORY_H
#define TESTSENSORFACTORY_H


#include <Encoders/IEncoderFactory.h>
#include <Sensor/ISensor.h>

namespace sensor{

	class TestSensorFactory
	{

	public:
		TestSensorFactory(encoders::IEncoderFactory* encoderFactory);

		//Creates a test sensor on the given pin number.  Updates from this sensor
		//	are called via the encoder at updateTimerIntervalMs periods.
		ISensor* CreateTestTemperatureSensor();



	private:
		encoders::IEncoderFactory* m_encoderFactory;

	};

}

#endif