

#include <boost/test/unit_test.hpp>

#include "Messaging/Temperature/TemperatureParser.h"
#include "Messaging/NanoPbCodec.h"

#include "Test Classes/TestMessageRouter.h"
#include "Test Classes/TestListener.h"



namespace messaging {
	namespace temperature {
		namespace test {
			struct TestFixture
			{
				TestFixture()
					:testRouter(new messaging::test::TestMessageRouter()),
					testListener(new testclasses::TestListener()),
					toTest("TESTGUID", testRouter)
				{
				}

				messaging::test::TestMessageRouter* testRouter;
				testclasses::TestListener* testListener;
				TemperatureParser toTest;
			};

		}
	}
}

BOOST_AUTO_TEST_SUITE(TemperatureParserTests)

BOOST_AUTO_TEST_CASE(ParseMessage)
{

	messaging::temperature::test::TestFixture fixture;

	//create a test message to be sent
	Temperature testTempMessage;
	float testTemp = 77.7f;
	testTempMessage.temperatureF = testTemp;

	Header header;

	const char* arduinoId = "ArduinoID";
	const char* sensorId = "SensorX";
	
	messaging::nanopb::copyString(arduinoId, header.arduinoId);
	messaging::nanopb::copyString(sensorId, header.sensorId);

	testTempMessage.header = header;

	//encode the message
	uint8_t* buffer = new uint8_t[256];
	int bufferSize = messaging::nanopb::encodeMessage<Temperature>(&testTempMessage, Temperature_fields, &buffer);

	bool success = fixture.toTest.parse(buffer, bufferSize);

	//check the listener for notification
	BOOST_CHECK(fixture.testListener->receivedTemperatureMessages.size() == 1);

	//check the fields
	BOOST_CHECK(fixture.testListener->receivedTemperatureMessages[0].temperatureF == testTemp);
	BOOST_CHECK(strcmp(arduinoId, fixture.testListener->receivedTemperatureMessages[0].header.arduinoId) == 0);
	BOOST_CHECK(strcmp(sensorId, fixture.testListener->receivedTemperatureMessages[0].header.sensorId) == 0);


}

BOOST_AUTO_TEST_CASE(SendTemperatureMessage)
{

	messaging::temperature::test::TestFixture fixture;

	Temperature temp;
	Header header;
	const char* arduinoId = "ArduinoID";
	const char* sensorId = "SensorX";

	messaging::nanopb::copyString(arduinoId, header.arduinoId);
	messaging::nanopb::copyString(sensorId, header.sensorId);

	temp.header = header;

	temp.temperatureF = 88.1f;

	//send the message
	fixture.toTest.sendTemperatureMessage(temp);


	//make sure the message was sent to the router
	BOOST_CHECK(fixture.testRouter->sentMessages.size() == 1);
	
	//get the message back out
	Temperature decodedTemp;
	bool success = messaging::nanopb::decodeMessage<Temperature>(fixture.testRouter->sentMessages[0].first, fixture.testRouter->sentMessages[0].second, Temperature_fields, decodedTemp);

	BOOST_CHECK(success);

	BOOST_CHECK(strcmp(arduinoId, decodedTemp.header.arduinoId) == 0);
	BOOST_CHECK(strcmp(sensorId, decodedTemp.header.sensorId) == 0);
	BOOST_CHECK(temp.temperatureF == decodedTemp.temperatureF);


}


BOOST_AUTO_TEST_CASE(CheckParserType)
{

	messaging::temperature::test::TestFixture fixture;

	BOOST_CHECK(fixture.toTest.getParserType() == messaging::IParser::ParserType::Temperature);

}





BOOST_AUTO_TEST_SUITE_END()