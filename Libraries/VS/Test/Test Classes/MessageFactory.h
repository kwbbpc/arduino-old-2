#ifndef MESSAGEFACTORY
#define MESSAGEFACTORY

#include "Messaging/Temperature/temperature.pb.h"
#include "Messaging/NanoPbCodec.h"

inline Temperature MakeTemperatureMessage(char* arduinoId, char* sensorId, float temp)
{

	Temperature t;
	Header h;

	messaging::nanopb::copyString(arduinoId, h.arduinoId);
	messaging::nanopb::copyString(sensorId, h.sensorId);

	t.header = h;

	t.temperatureF = temp;

	return t;

}

#endif
