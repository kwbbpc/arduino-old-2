

#ifndef ITEMPERATURESENSOR_H
#define ITEMPERATURESENSOR_H

#include "ISensor.h"

namespace sensor{ namespace temperature{

	class ITemperatureSensor : public ISensor
	{
	public : 

		virtual float getTemperatureF() = 0;
		virtual float getTemperatureC() = 0;

	};

}}


#endif
