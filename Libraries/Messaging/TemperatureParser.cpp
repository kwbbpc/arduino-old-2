

#include "TemperatureParser.h"

#include "ITemperatureListener.h"

#include "temperature.pb.h"

#include "NanoPbCodec.h"

#include "pb_decode.h"

#include "../utilities/LinkedList.h"

#include "MessageVersion.h"





namespace messaging {
	namespace temperature {


		Temperature TemperatureParser::MakeTemperatureMessage(sensor::temperature::ITemperatureSensor* temperatureSensor)
		{
			Temperature tempMsg = Temperature_init_zero;
			Header head = Header_init_zero;
			strcpy(head.arduinoId, m_arduinoGuid);
			strcpy(head.sensorId, temperatureSensor->getUniqueId());
			
			tempMsg.header = head;

			tempMsg.temperatureF = temperatureSensor->getTemperatureF();

			return tempMsg;
		}



		TemperatureParser::TemperatureParser(const char* arduinoGuid, messaging::IMessageRouter* router)
			:
			m_router(router),
			m_arduinoGuid(arduinoGuid)
		{
		}

		TemperatureParser::~TemperatureParser()
		{
		}

		bool TemperatureParser::parse(uint8_t* buffer, uint16_t bufferSize)
		{

			Temperature temperature = Temperature_init_zero;

			bool success = nanopb::decodeMessage<Temperature>(buffer, bufferSize, Temperature_fields, temperature);

			if (success)
			{
				//check that the guid matches
				if (strcmp(temperature.header.arduinoId, m_arduinoGuid) == 0)
				{
					//find the proper sensor to request the temp from
					for (TempSensorList_t::Iterator iter = m_temperatureSensors.begin();
					iter != m_temperatureSensors.end(); ++iter)
					{
						if (strcmp(temperature.header.sensorId, iter->getUniqueId()) == 0)
						{

							//get the temperature of this device & send it in response.
							Temperature t = MakeTemperatureMessage((*iter));
							success = sendTemperatureMessage(t);

						}
					}
				}
			}

		
			
			return success;
		}


		bool TemperatureParser::sendTemperatureMessage(Temperature& message)
		{

			uint8_t* buffer = new uint8_t[512];
			int bytesWritten = nanopb::encodeMessage<Temperature>(&message, Temperature_fields, &buffer);

			//write the buffer
			if (bytesWritten != 0)
			{
				m_router->sendMessage(IParser::ParserType::Temperature, buffer, bytesWritten);
			}
			
			delete[] buffer;

			//encoding succeeded if there were bytes written
			return bytesWritten != 0;

		}

		uint8_t TemperatureParser::getParserType()
		{
			return static_cast<uint8_t>(IParser::ParserType::Temperature);
		}

		void TemperatureParser::registerTemperatureSensor(sensor::temperature::ITemperatureSensor* temp)
		{
			m_temperatureSensors.add(temp);
		}

	}
}