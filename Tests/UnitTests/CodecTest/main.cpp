

#ifdef UNITTEST
#include <NanoPB/backupStdBool.h>
#endif

#include <NanoPB/pb.h>
#include <NanoPB/pb_encode.h>
#include <NanoPB/pb_decode.h>
#include <Test/TestTemperatureSensor.h>
#include <TestUtilities/HasMessageHelpers.h>
#include <assert.h>
#include <string>

#include <boost/shared_ptr.hpp>



#define BOOST_TEST_MODULE EncoderTests

#include <boost/test/unit_test.hpp>



static const std::string ServerGuid = "634E5819-240D-4D69-A792-07ECE4C3A3E1";

static const std::string PlatformGuid = "2AA334FE-A4F3-42E9-BF0D-9F7E0F25049F";
static const std::string SensorGuid = "9AFA5AB3-3491-4D93-BB4F-54817E0DBDC4";


struct TestFixture
{

	TestFixture()
	{
		server.has_platformGuid = true;
		strcpy(server.platformGuid,ServerGuid.c_str());
		server.has_sensorGuid = false;

		sensor.has_platformGuid = true;
		strcpy(sensor.platformGuid,PlatformGuid.c_str());
		sensor.has_sensorGuid = true;
		strcpy(sensor.sensorGuid,SensorGuid.c_str());
	}

	LogisticsInfo server;
	LogisticsInfo sensor;

};


//! Generically tests the encoding and decoding of a given message, and verifies the header
//! source - the source logistics info of the message
//! destination - the destination of the message
//! inputMessage - the message to encode
//! 
//! returns the decoded message for comparison
template<class T>
T TestMessageEncoding(LogisticsInfo* source, LogisticsInfo* destination, T& inputMessage)
{
	TestFixture fixture;

	uint8_t* outputBuffer = 0;
	uint16_t bufferSize = 0;

	BOOST_CHECK_MESSAGE(encoders::nanopb::encodeMessage<T>(source, destination, &inputMessage, &outputBuffer, bufferSize), "Failed to encode message");
	
	//now decode and check
	HeaderMessage decodedHeader;
	BOOST_CHECK_MESSAGE(encoders::nanopb::decodeHeader(outputBuffer, bufferSize, decodedHeader), "Failed to decode Header message");

	//compare the header to expected value
	HeaderMessage expectedHeader = testutil::makeHeaderMessage(encoders::nanopb::Version, encoders::getMessageType<T>(), destination, source);
	BOOST_CHECK_MESSAGE(testutil::CompareHeaderMessages(decodedHeader, expectedHeader), "Decoded headers do not match");

	T decodedMsg;
	BOOST_CHECK_MESSAGE(encoders::nanopb::decodeMessage<T>(decodedHeader, outputBuffer, bufferSize, decodedMsg, encoders::getFields<T>()), "Failed to decode message payload");

	delete[] outputBuffer;

	return decodedMsg;
}





BOOST_AUTO_TEST_SUITE(EncoderTests)


BOOST_AUTO_TEST_CASE( TestDiscoverBroadcast )
{

	TestFixture fixture;
	DiscoverMessage discover;

	DiscoverMessage output = TestMessageEncoding<DiscoverMessage>(&fixture.server, 0, discover);

	testutil::CompareDiscoverMessages(discover, output);

}

BOOST_AUTO_TEST_CASE( TestDiscover )
{

	TestFixture fixture;
	DiscoverMessage discover;

	DiscoverMessage output = TestMessageEncoding<DiscoverMessage>(&fixture.server, &fixture.sensor, discover);

	testutil::CompareDiscoverMessages(discover, output);

}


BOOST_AUTO_TEST_CASE( TestTemperature )
{

	TestFixture fixture;
	


	{
		TemperatureMessage temp;
		strcpy(temp.deviceName,"DeviceName");
		temp.has_deviceName = true;
		temp.temperatureF = 26;
		temp.has_temperatureF = true;
		TemperatureMessage output = TestMessageEncoding<TemperatureMessage>(&fixture.server, &fixture.sensor, temp);

		BOOST_CHECK_MESSAGE(testutil::CompareTemperatureMessage(temp, output), "Failed to properly decode a temperature message.");
	}

	{
		TemperatureMessage temp;
		temp.has_deviceName = false;
		temp.temperatureF = 831.018347f;
		temp.has_temperatureF = true;
	
		TemperatureMessage output = TestMessageEncoding<TemperatureMessage>(&fixture.server, &fixture.sensor, temp);

		BOOST_CHECK_MESSAGE(testutil::CompareTemperatureMessage(temp, output), "Failed to properly decode a temperature message.");

	}
	{
		TemperatureMessage temp;
		strcpy(temp.deviceName,"DeviceName");
		temp.has_deviceName = true;
		temp.has_temperatureF = false;

		TemperatureMessage output = TestMessageEncoding<TemperatureMessage>(&fixture.server, &fixture.sensor, temp);

		BOOST_CHECK_MESSAGE(testutil::CompareTemperatureMessage(temp, output), "Failed to properly decode a temperature message.");
	}
	{
		TemperatureMessage temp;
		temp.has_deviceName = false;
		temp.has_temperatureF = false;


		TemperatureMessage output = TestMessageEncoding<TemperatureMessage>(&fixture.server, &fixture.sensor, temp);

		BOOST_CHECK_MESSAGE(testutil::CompareTemperatureMessage(temp, output), "Failed to properly decode a temperature message.");
	}
}



BOOST_AUTO_TEST_SUITE_END()