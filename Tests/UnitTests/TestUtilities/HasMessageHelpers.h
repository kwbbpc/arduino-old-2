#ifndef HASMESSAGEHELPERS_H
#define HASMESSAGEHELPERS_H

#include <NanoPB\hasmessages\DiscoverMessage.pb.h>
#include <NanoPB\hasmessages\TemperatureMessage.pb.h>
#include <NanoPB\hasmessages\Header.pb.h>

#include <string>

namespace testutil{

	bool CompareHeaderMessages(const HeaderMessage& msg1, const HeaderMessage& msg2);
	
	bool CompareDiscoverMessages(const DiscoverMessage& msg1, const DiscoverMessage& msg2);

	bool CompareTemperatureMessage(const TemperatureMessage& msg1, const TemperatureMessage& msg2);

	HeaderMessage makeHeaderMessage(uint32_t version, HeaderMessage_MessageType messageType, const char* destPlatform,
		const char* destSensor, const char* origPlatform, const char* origSensor);
	HeaderMessage makeHeaderMessage(uint32_t version, _HeaderMessage_MessageType messageType, LogisticsInfo* dest,
		LogisticsInfo* orig);

	DiscoverMessage makeDiscoverMessage();


	TemperatureMessage makeTemperatureMessage(std::string* deviceName, float* temperatureF);


}

#endif
