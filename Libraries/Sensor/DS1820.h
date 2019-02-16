#ifndef DS1820_H
#define DS1820_H


#include "ITemperatureSensor.h"
#include "DallasTemperature.h"
#include "OneWire.h"


namespace sensor{ namespace temperature{

	class DS1820 : public ITemperatureSensor
	{

	public:

		DS1820(int dataPinNumber, const char* guid);

		//See ISensor
		virtual bool initialize();
		virtual const char* getUniqueId() const;
		virtual SensorType::Enum getType() const;
		virtual const char* getDeviceName() const;

		//See ITemperatureSensor
		virtual float getTemperatureF();
		virtual float getTemperatureC();
		

	private:

		int m_dataPinNumber;
		const char* m_guid;
		
		DeviceAddress m_thermometerAddress;
		DallasTemperature m_temperatureSensor;
		OneWire m_oneWire;
		
		

	};

}}

#endif