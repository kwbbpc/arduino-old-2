
#ifndef TESTMESSAGEROUTER_H
#define TESTMESSAGEROUTER_H

#include "Messaging/IMessageRouter.h"
#include "Messaging/IParser.h"

#include <cstdint>

#include <vector>
#include <string>
#include <utility>

namespace messaging{ namespace test{


	class TestMessageRouter : public IMessageRouter
	{
	public:
		TestMessageRouter();
		~TestMessageRouter();


		//Route a received message to the proper sensor
		//! buffer - the raw message received
		//! bufferSize - the size of the buffer
		virtual void routeMessage(uint8_t* buffer, int bufferSize) ;

		//Sends a messsage across the serial port
		//! buffer - pointer to the buffer containing the message
		//! bufferSize - the size of the message buffer
		virtual void sendMessage(IParser::ParserType::Enum parserType, uint8_t* buffer, int bufferSize);

		//register a parser with the message router so that the router
		//! can send this message to the correct parser for handling
		virtual void registerParser(IParser* parser);



		void clearMessages();

		void clearSentMessages();

		void clearRoutedMessages();

		std::vector<IParser*> registeredParsers;

		typedef std::pair<uint8_t*, int> MessagePair_t;
		
		std::vector<MessagePair_t> routedMessages;

		std::vector<MessagePair_t> sentMessages;
		
	};


}}

#endif