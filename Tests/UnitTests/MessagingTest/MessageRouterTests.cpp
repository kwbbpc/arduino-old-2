
#include <boost/test/unit_test.hpp>


#include <Test/TestSensor.h>
#include <Test/TestTemperatureSensor.h>
#include <Messaging/MessageRouter.h>
#include <NanoPB/MessageTypeTranslator.h>
#include <Serial/test/TestSerial.h>
#include <TestUtilities/HasMessageHelpers.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

BOOST_AUTO_TEST_SUITE(MessageRouterTests)

static const double TestTemp = 72.1;
static const std::string DeviceName = "DeviceName";

std::string PlatformGuid = "FF04FBA1-3997-4677-ACC6-099F71495B7B";
std::string ServerGuid = "4DB7D732-EDE8-4157-9DF5-B640FA0C7CF1";

std::string guid1 = "B9DBFD8A-2544-44F4-850B-80375E05EE95";
std::string guid2 = "B1E0CA6A-E79E-4045-A420-F798719ACE61";
std::string guid3 = "CE7C397E-5F2C-42AD-B526-7D37D8F9ACFF";

//these guids all resolve to the same hash
std::string guid4 = "FE7C397E-5F2C-42AD-B526-7D37D8F9ACFC";
std::string guid5 = "F7EC397E-5F2C-42AD-B526-7D37D8F9ACFC";
std::string guid6 = "F7EC397E-5F2C-42DA-B526-7D37D8F9ACFC";


std::string guidBogus = "XXXX";


static const HeaderMessage BroadcastHeader = testutil::makeHeaderMessage(encoders::nanopb::Version, encoders::getMessageType<HeaderMessage>(), 0, 0, ServerGuid.c_str(), 0);



struct TestFixture
{

	TestFixture():
	serialConnection(),
	router(PlatformGuid.c_str(), &serialConnection),
	testSensor1(1,guid1.c_str()),
	testSensor2(2,guid2.c_str()),
	testSensor3(3,guid3.c_str()),
	testSensor4(4,guid4.c_str()),
	testSensor5(5,DeviceName.c_str(),guid5.c_str()),
	testSensor6(6,DeviceName.c_str(),guid6.c_str()),
	encodedMessage(0),
	messageSize(0)
	{
		router.registerSensor(&testSensor1);
		router.registerSensor(&testSensor2);
		router.registerSensor(&testSensor3);
		router.registerSensor(&testSensor4);
		router.registerSensor(&testSensor5);
		router.registerSensor(&testSensor6);

		serverLocation.has_platformGuid = true;
		strcpy(serverLocation.platformGuid,ServerGuid.c_str());
		serverLocation.has_sensorGuid = false;
		
	}

	~TestFixture()
	{
		//no deletion of encoded message should be necessary.  
		//Cleanup of the message is handled by the message router.
	}

	serial::test::TestSerial serialConnection;
	
	messaging::MessageRouter router;

	LogisticsInfo serverLocation;

	
	uint8_t* encodedMessage;
	uint16_t messageSize;

	sensor::test::TestSensor testSensor1;
	sensor::test::TestSensor testSensor2;
	
	//these sensors should resolve to the same hash value.
	sensor::test::TestSensor testSensor3;
	sensor::test::TestSensor testSensor4;
	sensor::temperature::test::TestTempSensor testSensor5;
	sensor::temperature::test::TestTempSensor testSensor6;

};


BOOST_AUTO_TEST_CASE( TestSensorRegistration )
{

	//the fixture should automatically register the sensors with the router.
	TestFixture fixture;

	//verify test sensor 1 was registered and received a messaging connection
	BOOST_CHECK_MESSAGE(fixture.testSensor1.m_connection != 0, "The router failed to connect a registered sensor");

}

BOOST_AUTO_TEST_CASE( TestSendMessage )
{

	//the fixture should automatically register the sensors with the router.
	TestFixture fixture;

	std::string cBuffer = "This is a test message";
	const uint8_t* buffer = reinterpret_cast<const uint8_t*>(cBuffer.c_str());
	uint16_t bufferSize = cBuffer.size();

	fixture.router.sendMessage(buffer, bufferSize);

	//Check that the message was sent
	BOOST_CHECK_MESSAGE(fixture.serialConnection.writtenMessages.size() == 1, "The router failed to send a message.");
	
	BOOST_CHECK_MESSAGE(fixture.serialConnection.writtenMessages[0].second == cBuffer.size(), "Message router sent the wrong number of bytes.");

	for(int i=0; i<bufferSize; ++i)
	{
		BOOST_CHECK_MESSAGE(fixture.serialConnection.writtenMessages[0].first[i] == buffer[i], "Message router sending message validation failed at byte " << i);
	}

	

}


BOOST_AUTO_TEST_CASE( GoodDiscoverMessageBroadcast )
{
	TestFixture fixture;
	//Send a message with a good discover message
	DiscoverMessage disc = testutil::makeDiscoverMessage();

	encoders::nanopb::encodeMessage<DiscoverMessage>(&fixture.serverLocation, 0, &disc, &fixture.encodedMessage, fixture.messageSize);
	

	fixture.router.routeMessage(fixture.encodedMessage, fixture.messageSize);

	//Verify
	BOOST_CHECK_MESSAGE(fixture.testSensor1.receivedDiscoverMessages.size() == 1, "Test sensor 1 failed to receive broadcast message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor2.receivedDiscoverMessages.size() == 1, "Test sensor 2 failed to receive broadcast message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor3.receivedDiscoverMessages.size() == 1, "Test sensor 3 failed to receive broadcast message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor4.receivedDiscoverMessages.size() == 1, "Test sensor 4 failed to receive broadcast message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor5.receivedDiscoverMessages.size() == 1, "Test sensor 5 failed to receive broadcast message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor6.receivedDiscoverMessages.size() == 1, "Test sensor 6 failed to receive broadcast message.");

	//Check the message validity
	HeaderMessage header = fixture.testSensor1.receivedDiscoverMessages[0].first;
	DiscoverMessage receivedDiscover = fixture.testSensor1.receivedDiscoverMessages[0].second;
	
	testutil::CompareHeaderMessages(header, BroadcastHeader);

	
}



BOOST_AUTO_TEST_CASE( GoodTemperatureMessageBroadcast )
{

	TestFixture fixture;

	//Send a message with a good temp message to the second sensor
	TemperatureMessage temp = testutil::makeTemperatureMessage(0,0);
	
	encoders::nanopb::encodeMessage<TemperatureMessage>(&fixture.serverLocation, 0, &temp, &fixture.encodedMessage, fixture.messageSize);
	
	fixture.router.routeMessage(fixture.encodedMessage, fixture.messageSize);

	//Make sure the temperature sensors received the broadcast
	BOOST_CHECK_MESSAGE(fixture.testSensor5.receivedTemperatureMessages.size() == 1, "Test sensor 5 failed to received a broadcast temperature message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor6.receivedTemperatureMessages.size() == 1, "Test sensor 6 failed to received a broadcast temperature message.");
	
	//verify the message received
	testutil::CompareHeaderMessages(BroadcastHeader, fixture.testSensor5.receivedTemperatureMessages[0].first);
	testutil::CompareTemperatureMessage(temp, fixture.testSensor5.receivedTemperatureMessages[0].second);

	//make sure the other sensors didn't receive a message
	BOOST_CHECK_MESSAGE(fixture.testSensor1.receivedDiscoverMessages.size() == 0, "Test sensor 1 received a broadcast message when a temperature broadcast was sent.");


}

BOOST_AUTO_TEST_CASE( GoodTemperatureMessage )
{

	TestFixture fixture;

	//Send a message with a good temp message to the second sensor
	TemperatureMessage temp = testutil::makeTemperatureMessage(0,0);
	
	//route this message to a specific sensor
	LogisticsInfo destination;
	destination.has_platformGuid = true;
	strcpy(destination.platformGuid,PlatformGuid.c_str());
	destination.has_sensorGuid = true;
	strcpy(destination.sensorGuid, guid5.c_str());

	encoders::nanopb::encodeMessage<TemperatureMessage>(&fixture.serverLocation, &destination, &temp, &fixture.encodedMessage, fixture.messageSize);
	
	fixture.router.routeMessage(fixture.encodedMessage, fixture.messageSize);

	//Make sure the right temperature sensor received the message
	BOOST_CHECK_MESSAGE(fixture.testSensor5.receivedTemperatureMessages.size() == 1, "Test sensor 5 failed to received a temperature message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor6.receivedTemperatureMessages.size() == 0, "Test sensor 6 incorrectly received a temperature message.");
	
	//verify the message received
	testutil::CompareHeaderMessages(BroadcastHeader, fixture.testSensor5.receivedTemperatureMessages[0].first);
	testutil::CompareTemperatureMessage(temp, fixture.testSensor5.receivedTemperatureMessages[0].second);
			
	
}

BOOST_AUTO_TEST_CASE( BadSensorBroadcast )
{

	TestFixture fixture;

	//Send a message with a good temp message to the second sensor
	TemperatureMessage temp = testutil::makeTemperatureMessage(0,0);
	
	//route this message to a specific sensor
	LogisticsInfo destination;
	destination.has_platformGuid = true;
	strcpy(destination.platformGuid,PlatformGuid.c_str());
	destination.has_sensorGuid = true;
	strcpy(destination.sensorGuid, guid5.c_str());

	encoders::nanopb::encodeMessage<TemperatureMessage>(&fixture.serverLocation, &destination, &temp, &fixture.encodedMessage, fixture.messageSize);
	
	fixture.router.routeMessage(fixture.encodedMessage, fixture.messageSize);

	//Make sure the right temperature sensor received the message
	BOOST_CHECK_MESSAGE(fixture.testSensor5.receivedTemperatureMessages.size() == 1, "Test sensor 5 failed to received a temperature message.");
	BOOST_CHECK_MESSAGE(fixture.testSensor6.receivedTemperatureMessages.size() == 0, "Test sensor 6 incorrectly received a temperature message.");
	
	//verify the message received
	testutil::CompareHeaderMessages(BroadcastHeader, fixture.testSensor5.receivedTemperatureMessages[0].first);
	testutil::CompareTemperatureMessage(temp, fixture.testSensor5.receivedTemperatureMessages[0].second);
			
	
}



/* TODO
BOOST_AUTO_TEST_CASE( BadSensorGuidRouting )
{
	TestFixture fixture;
	

	//send it to a bogus sensor
	HeaderMessage header = testutil::makeHeaderMessage(99, true,false,0,true,guidBogus,true,true,ServerGuid,false,0);
	TemperatureMessage temp = testutil::makeTemperatureMessage("test",0.0f);

	HasMessage msgTemp = testutil::makeMessage(&header,0,&temp);
		

	fixture.router.routeMessage(msgTemp);
	
	
}
TODO
*/

BOOST_AUTO_TEST_SUITE_END()