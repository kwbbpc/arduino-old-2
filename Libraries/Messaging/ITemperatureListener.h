
#ifndef ITEMPERATURELISTENER
#define ITEMPERATURELISTENER

#include "temperature.pb.h"

namespace messaging {
	namespace temperature {

		class ITemperatureListener
		{

		public:
			//Called when there is a temperature message for the sensor.  The new message
			// is provided as a parameter to the listener
			virtual void onTemperature(Temperature message) = 0;

		};

	}
}

#endif
