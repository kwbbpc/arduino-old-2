
#include "MessageRouter.h"
#include "../Utilities/LinkedList.h"
#include "MessageVersion.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace messaging{


	MessageRouter::MessageRouter(serial::ISerialConnection* serial)
		:m_serial(serial)
	{

	}

	MessageRouter::~MessageRouter()
	{

	}

	void MessageRouter::routeMessage(uint8_t* buffer, int bufferSize)
	{

		//take off the first two bytes for version and message type
		uint8_t version = buffer[0];
		uint8_t messageType = buffer[1];

		uint8_t* message = new uint8_t[bufferSize - 2];

		for (int i = 2; i < bufferSize; ++i)
		{
			message[i - 2] = buffer[i];
		}

		//check the message version
		if (version != MESSAGE_VERSION)
			return;

		//send the message to the correct parser
		bool success = false;
		for (LinkedList<IParser*>::Iterator iter = m_parsers.begin(); iter != m_parsers.end(); ++iter)
		{
			if ((*iter)->getParserType() == messageType)
			{
				(*iter)->parse(message, bufferSize - 2);
				success = true;
			}
		}
		
		if (!success)
		{
			//no parsers received this message
		}

	}


	void MessageRouter::registerParser(IParser* parser)
	{
		m_parsers.add(parser);
	}

	
	void MessageRouter::sendMessage(IParser::ParserType::Enum type, uint8_t* buffer, int bufferSize)
	{

		//tack on the version and parser type
		int bufferOffset = 2;
		int finalBufferSize = bufferSize + bufferOffset;
		uint8_t* finalBuffer = new uint8_t[finalBufferSize];
		finalBuffer[0] = MESSAGE_VERSION;
		finalBuffer[1] = static_cast<uint8_t>(type);

		//copy the buffer
		for (int i = bufferOffset; i < finalBufferSize; ++i)
		{
			finalBuffer[i] = buffer[i - bufferOffset];
		}
		
		//send it
		m_serial->write(finalBuffer, finalBufferSize);
	}


}