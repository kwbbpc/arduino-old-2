
#include "TestMessageRouter.h"

namespace{
	void clearMessages(std::vector<messaging::test::TestMessageRouter::MessagePair_t>& messages)
	{
		for (std::vector<messaging::test::TestMessageRouter::MessagePair_t>::iterator mesVec = messages.begin();
		mesVec != messages.end(); ++mesVec)
		{
			delete[] mesVec->first;
		}
	}
}

namespace messaging{ namespace test{


	TestMessageRouter::TestMessageRouter()
	{
	}

	TestMessageRouter::~TestMessageRouter()
	{
		//clean up messages stored in the vectors
		clearMessages();
	}

	void TestMessageRouter::clearMessages()
	{
		clearSentMessages();
		clearRoutedMessages();
	}


	void TestMessageRouter::clearSentMessages()
	{
		::clearMessages(sentMessages);
	}

	void TestMessageRouter::clearRoutedMessages()
	{
		::clearMessages(routedMessages);
	}

	void TestMessageRouter::routeMessage(uint8_t* buffer, int bufferSize)
	{
		routedMessages.push_back(std::make_pair(buffer, bufferSize));
	}
	void TestMessageRouter::registerParser(IParser* parser)
	{	
		registeredParsers.push_back(parser);
	}

	void TestMessageRouter::sendMessage(IParser::ParserType::Enum type, uint8_t* buffer,  int bufferSize)
	{
		sentMessages.push_back(std::make_pair(buffer, bufferSize));
	}



}}