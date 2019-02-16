#ifndef TESTSENSOR_H
#define TESTSENSOR

#include <SensorType\SensorType.h>
#include <Sensor\ISensor.h>
#include <Encoders\ISensorEncoder.h>
#include <HasTemperature\ITemperatureSensor.h>

namespace sensor{ namespace temperature{

	class TestTemperatureSensor : public ITemperatureSensor
	{
	  public: 

		  TestTemperatureSensor(encoders::ISensorEncoder* encoder);

		  //performs initialization of the sensor
		  virtual bool initialize();

		  //tells the sensor to use its encoder and send a new update
		  virtual void sendUpdate();

		  //get the sensors unique GUID
		  virtual char* getUniqueId();

		  //gets the sensor type
		  virtual SensorType::Enum getType();    

		  virtual float getTemperatureC();
		  virtual float getTemperatureF();
		  virtual char* getDeviceName();

		  encoders::ISensorEncoder* m_encoder;
	};

}}

#endif