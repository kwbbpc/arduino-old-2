#ifndef TEMPERATUREPARSER
#define TEMPERATUREPARSER

#include "ITemperatureListener.h"

#include "Messaging/IParser.h"
#include "temperature.pb.h"
#include "Messaging/IMessageRouter.h"
#include "Utilities/LinkedList.h"
#include "Sensor/ITemperatureSensor.h"

namespace messaging {
	namespace temperature {

		
		class TemperatureParser : public IParser
		{

		public:

			TemperatureParser(const char* arduinoGuid, messaging::IMessageRouter* router);
			~TemperatureParser();

			virtual bool parse(uint8_t* buffer, uint16_t bufferSize);

			virtual uint8_t getParserType();

			//Registers a sensor with this parser
			void registerTemperatureSensor(sensor::temperature::ITemperatureSensor* t);

			bool sendTemperatureMessage(Temperature& message);



		private:

			Temperature MakeTemperatureMessage(sensor::temperature::ITemperatureSensor* temperatureSensor);

			IMessageRouter* m_router;

			LinkedList<ITemperatureListener*> m_listeners;

			typedef LinkedList<sensor::temperature::ITemperatureSensor*> TempSensorList_t;
			TempSensorList_t m_temperatureSensors;

			const char* m_arduinoGuid;

		};


	}
}

#endif