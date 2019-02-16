
#include <boost/test/unit_test.hpp>


#include <Test/TestSensor.h>
#include <Test/TestTemperatureSensor.h>
#include <Messaging/MessageRouter.h>
#include <NanoPB/MessageTypeTranslator.h>
#include <Serial/test/TestSerial.h>
#include <Test/TestMessageRouter.h>


BOOST_AUTO_TEST_SUITE(MessagingConnectionTests)


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

struct TestFixture
{

	TestFixture():
	router(PlatformGuid.c_str()),
	testSensor1(1,guid1.c_str())
	{
		

		serverLocation.has_platformGuid = true;
		strcpy(serverLocation.platformGuid,ServerGuid.c_str());
		serverLocation.has_sensorGuid = false;
		
	}

	~TestFixture()
	{
	}

	
	messaging::test::TestMessageRouter router;

	LogisticsInfo serverLocation;

	sensor::test::TestSensor testSensor1;

};


BOOST_AUTO_TEST_CASE(TestBroadcastSend)
{

	TestFixture fixture;

	DiscoverMessage message;

	fixture.router.registerSensor(&fixture.testSensor1);

	//send a broadcast message
	fixture.testSensor1.sendMessage<DiscoverMessage>(message);

	//ensure the message was sent to the router for writing
	BOOST_CHECK_MESSAGE(fixture.router.sentMessages.size() == 1, "Failed to send message to message router");

	//make sure the message was a broadcast message
	HeaderMessage header;
	BOOST_CHECK_MESSAGE(encoders::nanopb::decodeHeader(fixture.router.sentMessages[0].first, fixture.router.sentMessages[0].second, header), "Failed to decode header message");
	BOOST_CHECK_MESSAGE(!header.has_destination, "Sent a single message when it should have been a broadcast");

	
}

BOOST_AUTO_TEST_CASE(TestSingleSend)
{

	TestFixture fixture;

	fixture.router.registerSensor(&fixture.testSensor1);

	//send a message
	fixture.testSensor1.sendUpdate(fixture.serverLocation);

	//ensure the message was sent to the router for writing
	BOOST_CHECK_MESSAGE(fixture.router.sentMessages.size() == 1, "Failed to send message to message router");
	

}


BOOST_AUTO_TEST_SUITE_END()