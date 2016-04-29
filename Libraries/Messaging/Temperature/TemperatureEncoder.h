#ifndef TEMPERATUREENCODER_H
#define TEMPERATUREENCODER_H

#include "NanoPbEncoderFactory.h"
#include "ISensorEncoder.h"
#include "../HasTemperature/ITemperatureSensor.h"
#include "../Sensor/ISensor.h"


namespace encoders { namespace nanopb{

	//handles encoding and decoding of messages for the temperature sensor.
	class TemperatureEncoder : public encoders::ISensorEncoder
	{

	public:

		static const int TemperatureMessageBufferSize = 512;

		TemperatureEncoder(encoders::nanopb::NewDataFn newDataFn);

		virtual bool sendNewMessage(sensor::ISensor* sensor, const LogisticsInfo& destination);
		virtual void sendError(char* errorStr);

	private:

		NewDataFn m_dataFn;
		const uint32_t version = 1;

	};

}}



#endif