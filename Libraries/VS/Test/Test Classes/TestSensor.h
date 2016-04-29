#ifndef TESTSENSOR_H
#define TESTSENSOR_H

#include "../Sensor/ISensor.h"
#include "../SensorType/SensorType.h"

#include "../Utilities/LinkedList.h"

#include "../NanoPB/hasmessages/Header.pb.h"
#include "../NanoPB/hasmessages/DiscoverMessage.pb.h"
#include "../NanoPB/hasmessages/TemperatureMessage.pb.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace sensor{ namespace test{

	


	class TestSensor : public ISensor
	{  
	public: 

		  TestSensor(int id, const char* guid = "0FCDFFCE-255E-4B17-8AAD-BACB261C4660");
		  ~TestSensor();

		  
		  //Message processor
		  virtual void processMessage(const HeaderMessage& header, const DiscoverMessage& msg);

		  //ISensor Interface
		  virtual bool initialize();
		  virtual void sendUpdate(const LogisticsInfo& destination);
		  virtual const char* getUniqueId();
		  virtual SensorType::Enum getType();
		  virtual void connect(messaging::MessagingConnection* connection);

		  //testing methods
		  template<class T>
		  void sendMessage(const T& msg)
		  {
			  m_connection->sendMessage(msg);
		  }

		  template<class T>
		  void sendMessage(const LogisticsInfo& info, const T& msg)
		  {
			  m_connection->sendMessage(info, msg);
		  }


	//public members for testing.
	public:
		  int m_id;
		  const char* m_guid;


		  messaging::MessagingConnection* m_connection;

		  typedef std::pair<HeaderMessage, DiscoverMessage> ReceivedDiscoverMessage;
		  std::vector<ReceivedDiscoverMessage> receivedDiscoverMessages;

	};


	typedef boost::shared_ptr<TestSensor> TestSensorPtr;

}}

#endif