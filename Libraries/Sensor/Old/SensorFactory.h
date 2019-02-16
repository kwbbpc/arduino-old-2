#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H


#include "../Encoders/IEncoderFactory.h"
#include <ISensor.h>

namespace sensor{

	class SensorFactory
	{

	public:
		SensorFactory(encoders::IEncoderFactory* encoderFactory);

		//Creates a DS1820S sensor on the given pin number.  Updates from this sensor
		//	are called via the encoder at updateTimerIntervalMs periods.
		ISensor* CreateDs1820(int pinNumber, int updateTimerIntervalMs, const char* guid);



	private:
		encoders::IEncoderFactory* m_encoderFactory;

	};

}

#endif