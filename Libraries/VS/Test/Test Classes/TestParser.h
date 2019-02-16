#ifndef TESTPARSER
#define TESTPARSER

#include <vector>

#include "Messaging\IParser.h"


namespace testclasses {

	class TestParser : public messaging::IParser
	{
	public:

		TestParser();

		//Parses a message coming through for this type of parser
		virtual bool parse(uint8_t* buffer, uint16_t bufferSize);

		virtual uint8_t getParserType();

		void setParserType(messaging::IParser::ParserType::Enum type);


		typedef std::pair<uint8_t*, int> Message_t;
		std::vector<Message_t> parsedMessages;
		messaging::IParser::ParserType::Enum parserType;

	};

}

#endif
