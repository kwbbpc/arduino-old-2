
#include "TestParser.h"

namespace testclasses {

		TestParser::TestParser()
		{
			parserType = messaging::IParser::ParserType::Invalid;
		}

		
		bool TestParser::parse(uint8_t* buffer, uint16_t bufferSize)
		{
			parsedMessages.push_back(std::make_pair(buffer, bufferSize));

			return true;
		}

		uint8_t TestParser::getParserType()
		{
			return parserType;
		}

		void TestParser::setParserType(messaging::IParser::ParserType::Enum type)
		{
			parserType = type;
		}



}