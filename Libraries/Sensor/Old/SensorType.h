#ifndef SENSORTYPE_H
#define SENSORTYPE_H


namespace sensor{

	struct SensorType
	{
		enum Enum
		{
			Temperature,
			Thermostat,
			LightSensor,
			LightSwitch,
			Blinds,
			Webcam,
			CarbonMonoxide,
			Humidity,
			MAX,


			INVALID = -1
		};

		static char* translator(Enum type);

		static const Enum translator(char* type);

	};  

}

#endif