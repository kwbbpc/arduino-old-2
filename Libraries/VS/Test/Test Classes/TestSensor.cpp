
#include "TestSensor.h"
#include "../Messaging/MessagingConnection.h"
#include <string.h>

namespace sensor{ namespace test{
	
	TestSensor::TestSensor(int id, const char* guid)
		:m_guid(guid),
		m_id(id),
		m_connection(0)
	{
	}

	TestSensor::~TestSensor()
	{
		//cleanup the connection since we're going down.
		if(m_connection != 0)
		{
			//delete m_connection;
		}
	}

	bool TestSensor::initialize()
	{
		return true;
	}
	
	void TestSensor::sendUpdate(const LogisticsInfo& destination)
	{
		TemperatureMessage message;
		strcpy(message.deviceName,"TestSensor");
		message.temperatureF = 89.9f;

		if(m_connection)
		{
			m_connection->sendMessage(&destination,message);
		}
	}

	const char* TestSensor::getUniqueId()
	{
		return m_guid;
	}
	
	SensorType::Enum TestSensor::getType()
	{
		return SensorType::INVALID;
	}
	
	void TestSensor::processMessage(const HeaderMessage& header, const DiscoverMessage& msg)
	{
		receivedDiscoverMessages.push_back(ReceivedDiscoverMessage(header,msg));
	}

	void TestSensor::connect(messaging::MessagingConnection* connection)
	{
		m_connection = connection;
	}



}}