#include "HasMessageHelpers.h"



#include <stdlib.h>
#include <string.h>
#include <string>

namespace testutil{

	bool CompareLogisticInfos(const LogisticsInfo& msg1, const LogisticsInfo& msg2)
	{
		bool success = true;
		success &= msg1.has_platformGuid == msg2.has_platformGuid;
		if(msg1.has_platformGuid)
		{
			success &= (strcmp(msg1.platformGuid, msg2.platformGuid) == 0);
		}

		success &= msg1.has_sensorGuid == msg2.has_sensorGuid;
		if(msg1.has_sensorGuid)
		{
			success &= (strcmp(msg1.sensorGuid, msg2.sensorGuid) == 0);
		}

		return success;
	}

	bool CompareHeaderMessages(const HeaderMessage& msg1, const HeaderMessage& msg2)
	{
		bool success = true;
		success &= msg1.version == msg2.version;
		success &= msg1.message_type == msg2.message_type;
		success &= msg1.has_destination == msg2.has_destination;

		if(msg1.has_destination)
		{
			//compare the logistic infos
			success &= CompareLogisticInfos(msg1.destination, msg2.destination);
		}

		success &= msg1.has_origination == msg2.has_origination;
		if(msg1.has_origination)
		{
			success &= CompareLogisticInfos(msg1.origination, msg2.origination);
		}

		return success;
	}

	bool CompareDiscoverMessages(const DiscoverMessage& msg1, const DiscoverMessage& msg2)
	{
		bool success = true;
		return success;
	}

	bool CompareTemperatureMessage(const TemperatureMessage& msg1, const TemperatureMessage& msg2)
	{
		bool success = true;
		
		success &= (msg1.has_temperatureF == msg2.has_temperatureF);
		if(msg1.has_temperatureF)
		{
			success &= (msg1.temperatureF == msg2.temperatureF);
		}

		success &= (msg1.has_deviceName == msg2.has_deviceName);
		if(msg1.has_deviceName)
		{
			success &= strcmp(msg1.deviceName, msg1.deviceName) == 0;
		}

		return success;

	}

	HeaderMessage makeHeaderMessage(uint32_t version, _HeaderMessage_MessageType messageType, LogisticsInfo* dest,
		LogisticsInfo* orig)
	{
		HeaderMessage msg;
		
		msg.version = version;

		msg.message_type = messageType;

		msg.has_destination = (dest != 0);
		
		msg.has_origination = (orig != 0);
		
		if(msg.has_destination)
		{
			msg.destination = *dest;
		}

		if(msg.has_origination)
		{
			msg.origination = *orig;
		}

		return msg;
	}


	HeaderMessage makeHeaderMessage(uint32_t version, _HeaderMessage_MessageType messageType, const char* destPlatform,
		const char* destSensor, const char* origPlatform,
		const char* origSensor)
	{
		
		LogisticsInfo destinationInfo;
		LogisticsInfo sourceInfo;
				
		destinationInfo.has_platformGuid = (destPlatform != 0);
		if(destinationInfo.has_platformGuid)
		{
			strcpy_s(destinationInfo.platformGuid, destPlatform);
		}
		destinationInfo.has_sensorGuid = (destSensor != 0);
		if(destinationInfo.has_sensorGuid)
		{
			strcpy_s(destinationInfo.sensorGuid, destSensor);
		}
		

		sourceInfo.has_platformGuid = (origPlatform != 0);
		if(sourceInfo.has_platformGuid)
		{
			strcpy_s(sourceInfo.platformGuid, origPlatform);
		}
		sourceInfo.has_sensorGuid = (origSensor != 0);
		if(sourceInfo.has_sensorGuid)
		{
			strcpy_s(sourceInfo.sensorGuid, origSensor);
		}
		
		LogisticsInfo* destinationInfoToSend = 0;
		LogisticsInfo* sourceInfoToSend = 0;

		if(destPlatform != 0 || destSensor != 0)
		{
			destinationInfoToSend = &destinationInfo;
		}
		if(origPlatform != 0 || origSensor != 0)
		{
			sourceInfoToSend = &sourceInfo;
		}

		return makeHeaderMessage(version, messageType, destinationInfoToSend, sourceInfoToSend);

	}

	DiscoverMessage makeDiscoverMessage()
	{
		DiscoverMessage msg;
		return msg;
	}

	TemperatureMessage makeTemperatureMessage(std::string* deviceName, float* temperatureF)
	{
		TemperatureMessage msg;

		msg.has_deviceName = deviceName != 0;
		if(msg.has_deviceName)
		{
			strcpy_s(msg.deviceName,deviceName->c_str());
		}

		msg.has_temperatureF = temperatureF != 0;
		if(msg.has_temperatureF)
		{
			msg.temperatureF = *temperatureF;
		}

		return msg;
	}



}