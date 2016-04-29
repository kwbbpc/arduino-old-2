#ifndef IPARSER
#define IPARSER

#include <stdint.h>

#include "../Sensor/ISensor.h"


namespace messaging {


	class IParser
	{
	public:
		//Max value is 255 (1 byte)
		struct ParserType
		{
			enum Enum
			{
				Temperature = 0,

				Max,
				Invalid = -1
				
			};
		};
		
		//Parses a message coming through for this type of parser
		virtual bool parse(uint8_t* buffer, uint16_t bufferSize) = 0;

		virtual uint8_t getParserType() = 0;

		
	};
}


#endif