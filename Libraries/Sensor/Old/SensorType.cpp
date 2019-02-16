#include <SensorType.h>
#include <string.h>
#include <stdio.h>

namespace sensor{

	char* SensorType::translator(Enum type)
	{
		char retVal[10];
		sprintf(retVal,"%d",type);
		return retVal;
	}

	const SensorType::Enum SensorType::translator(char* type)
	{

		if(strcmp(type,translator(Temperature)) == 0)
			return SensorType::Temperature;
		if(strcmp(type,translator(Thermostat)) == 0)
			return SensorType::Thermostat;
		if(strcmp(type,translator(LightSensor)) == 0)
			return SensorType::LightSensor;
		if(strcmp(type,translator(LightSwitch)) == 0)
			return SensorType::LightSwitch;
		if(strcmp(type,translator(Blinds)) == 0)
			return SensorType::Blinds;
		if(strcmp(type,translator(Webcam)) == 0)
			return SensorType::Webcam;
		if(strcmp(type,translator(CarbonMonoxide)) == 0)
			return SensorType::CarbonMonoxide;
		if(strcmp(type,translator(Humidity)) == 0)
			return SensorType::Humidity;

		return INVALID;
	} 

}