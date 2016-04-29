#ifndef PARSER_H
#define PARSER_H


#include "IParser.h"

namespace messaging{


	class Parser : IParser
	{
	public:
		
		Parser(ISerialInterface serial);

		bool parse(uint8_t* buffer, int numberOfBytes);
		
		bool send( int numberOfBytes);
		
	private:
		IMessageRouter* m_router;
		const char* m_boardGuid;

	};


}


#endif