

#include "DS1820.h"



namespace sensor{ namespace temperature{


DS1820::DS1820(int dataPinNumber, const char* guid):
m_dataPinNumber(dataPinNumber),
m_oneWire(dataPinNumber),
m_temperatureSensor(&m_oneWire),
m_guid(guid)
{

}

//initializes the DS1820S sensor
bool DS1820::initialize()
{

	bool success = true;
	// search for devices on the bus and assign based on an index.  ideally,
	// you would do this to initially discover addresses on the bus and then 
	// use those addresses and manually assign them (see above) once you know 
	// the devices on your bus (and assuming they don't change).
	success &= m_temperatureSensor.getAddress(m_thermometerAddress, 0);

	if (success)
	{
		// set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
		success &= m_temperatureSensor.setResolution(m_thermometerAddress, 9);
	}

	return success;
		
}


float DS1820::getTemperatureC()
{
	m_temperatureSensor.requestTemperatures();
	return m_temperatureSensor.getTempC(m_thermometerAddress);
}

float DS1820::getTemperatureF()
{
	m_temperatureSensor.requestTemperatures();
	float tempC = m_temperatureSensor.getTempC(m_thermometerAddress);
	return DallasTemperature::toFahrenheit(tempC);
}

const char* DS1820::getDeviceName() const
{
	return "DS1820\0";
}

sensor::SensorType::Enum DS1820::getType() const
{
	return SensorType::Temperature;
}

const char* DS1820::getUniqueId() const
{
	return m_guid;
}


}}