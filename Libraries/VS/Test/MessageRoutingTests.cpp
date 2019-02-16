

#include <boost/test/unit_test.hpp>

#include "Messaging/NanoPbCodec.h"
#include "Messaging\MessageRouter.h"
#include "Messaging\MessageVersion.h"

#include "Test Classes/TestSerial.h"
#include "Test Classes/TestParser.h"
#include "Test Classes/TestListener.h"
#include "Test Classes/MessageFactory.h"



namespace messaging {
	namespace test {

		struct TestFixture
		{
			TestFixture()
				:testSerial(new serial::test::TestSerial()),
				toTest(testSerial)
			{
				testParser.setParserType(messaging::IParser::ParserType::Temperature);
				toTest.registerParser(&testParser);

			}

			const char* boardGuid = "ArduinoId";
			serial::ISerialConnection* testSerial;
			testclasses::TestParser testParser;
			MessageRouter toTest;
		};

	}
}

BOOST_AUTO_TEST_SUITE(TemperatureParserTests)

BOOST_AUTO_TEST_CASE(TestRouteMessage)
{

	messaging::test::TestFixture fixture;
	
	
	uint8_t* buffer;


	//setup the message
	char* aid = "ArduinoID";
	char* sid = "SensorID";
	float t = 183.2f;
	Temperature msg = MakeTemperatureMessage(aid, sid, t);
	
	int size = messaging::nanopb::encodeMessage(&msg, Temperature_fields, &buffer);

	int versionSize = 2;
	uint8_t* bufferVersion = new uint8_t[versionSize];
	uint8_t* finalBuffer = new uint8_t[versionSize + size];

	//setup the message version and type
	finalBuffer[0] = MESSAGE_VERSION;
	finalBuffer[1] = static_cast<uint8_t>(messaging::IParser::ParserType::Temperature);
	//combine the buffers
	for (int i = 0; i < size; ++i)
	{
		finalBuffer[i + versionSize] = buffer[i];
	}

	fixture.toTest.routeMessage(finalBuffer, size + versionSize);

	//make sure the listener got the message
	BOOST_CHECK(fixture.testParser.parsedMessages.size() == 1);

	//decode
	testclasses::TestParser::Message_t msgD = fixture.testParser.parsedMessages[0];
	Temperature decodedT;
	bool success = messaging::nanopb::decodeMessage(msgD.first, msgD.second, Temperature_fields, decodedT);

	BOOST_CHECK(success);
	BOOST_CHECK(decodedT.temperatureF == t);
	BOOST_CHECK(strcmp(decodedT.header.arduinoId, aid) == 0);
	BOOST_CHECK(strcmp(decodedT.header.sensorId, sid) == 0);



}

BOOST_AUTO_TEST_CASE(TestInvalidRouteMessage)
{

	messaging::test::TestFixture fixture;

	//setup the message version and type


}


BOOST_AUTO_TEST_CASE(TestSendMessage)
{

	messaging::test::TestFixture fixture;



}


BOOST_AUTO_TEST_CASE(TestRejectMessage)
{

	messaging::test::TestFixture fixture;


}

BOOST_AUTO_TEST_SUITE_END()