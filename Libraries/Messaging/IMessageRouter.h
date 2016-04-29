#ifndef IMESSAGEROUTER_H
#define IMESSAGEROUTER_H


#include "IParser.h"

namespace messaging{
	
	class IMessageRouter
	{
	public: 

		//Route a received message to the proper sensor
		//! buffer - the raw message received
		//! bufferSize - the size of the buffer
		virtual void routeMessage(uint8_t* buffer, int bufferSize) = 0;

		//Sends a messsage across the serial port
		//! buffer - pointer to the buffer containing the message
		//! bufferSize - the size of the message buffer
		virtual void sendMessage(IParser::ParserType::Enum type, uint8_t* buffer, int bufferSize) = 0;

		//register a parser with the message router so that the router
		//! can send this message to the correct parser for handling
		virtual void registerParser(IParser* parser) = 0;


	};

}

#endif