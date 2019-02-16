

#include "TemperatureEncoder.h"
#include "../HasTemperature/ITemperatureSensor.h"

#include <TestUtilities\HasMessageHelpers.h>
#include <NanoPB/pb.h>
#include <NanoPB/pb_encode.h>

//#include "../NanoPB/hasmessages/hasmessage.pb.h"
#include "../NanoPB/hasmessages/TemperatureMessage.pb.h"
#include <string.h>

namespace encoders { namespace nanopb{


	TemperatureEncoder::TemperatureEncoder(NewDataFn newDataFn):
	m_dataFn(newDataFn)
	{}

	void TemperatureEncoder::sendError(char* errorStr)
	{
		/* FUTURE
		uint8_t buffer[128];
		size_t message_length;

		Error errorMessage;

		//create the stream that will write to the buffer
		pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

		//fill out the message
		errorMessage.error = errorStr;

		//encode the message
		bool success = pb_encode(&stream, Error_fields, &errorMessage);

		if(!success)
		{
			//write a failure message
			Serial.write("Failed to encode error message!");
		}
		else
		{
			//send the message
			m_dataFn(buffer);
		}
		*/
	}


	bool TemperatureEncoder::sendNewMessage(sensor::ISensor* sensor, const LogisticsInfo& destination)
	{
		//cast the sensor to a temperature sensor
		sensor::temperature::ITemperatureSensor* pTempSensor = static_cast<sensor::temperature::ITemperatureSensor*>(sensor);

		if(!pTempSensor)
		{
			//send an error
			sendError("Temperature message failed to send, invalid sensor!");
			return false;
		}

		//must declare the buffer new here so it doesn't disappear on the end user
		uint8_t buffer[TemperatureMessageBufferSize];
		HasMessage message;
		testutil::makeHeaderMessage(version, destination.platformGuid, destination.sensorGuid, m_boardGuid, sensor->getUniqueId());
		TemperatureMessage temperatureMessage;

		//create the stream that will write to the buffer
		pb_ostream_t stream = pb_ostream_from_buffer(buffer, TemperatureMessageBufferSize);

		//fill out the message
		temperatureMessage.temperatureF = pTempSensor->getTemperatureF();
		strcpy_s(temperatureMessage.deviceName, pTempSensor->getDeviceName());
		strcpy_s(temperatureMessage.deviceGuid, pTempSensor->getUniqueId());

		//encode the message
		bool success = pb_encode(&stream, TemperatureMessage_fields, &temperatureMessage);
		size_t messageLength = stream.bytes_written;

		if(!success)
		{
			//write a failure message
			sendError("Failed to encode temperature message!");
			return false;
		}
		else
		{
			//send the message
			m_dataFn(buffer, messageLength);
			return true;
		}

		

	}


}}