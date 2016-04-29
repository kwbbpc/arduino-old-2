
#include "Parser.h"

#include "../NanoPB/hasmessages/hasmessage.pb.h"

namespace messaging{


	Parser::Parser(IMessageRouter* router, const char* boardGuid)
		:m_router(router),
		m_boardGuid(boardGuid)
	{

	}

	void Parser::registerSensor(sensor::ISensor* sensor)
	{
		m_router->registerSensor(sensor);
	}

	bool Parser::parse(uint8_t* buffer, int numberOfBytes)
	{

		//decode the message enough to pull out the destination ID

		//make a stream to read from the buffer
		pb_istream_t istream = pb_istream_from_buffer(buffer, numberOfBytes);

		//pull out the header and check if this is the destination board
		HasMessage has;
		bool success = pb_decode(&istream, HasMessage_fields, &has);

		if(success)
		{
			//if the message was a broadcast, or if the end destination is this board, process it
			if((!has.header.has_destination) || (strcmp(has.header.destination.platformGuid, m_boardGuid) == 0))
			{
				//route the message
				m_router->routeMessage(has);
			}
		}

		return success;

	}


}