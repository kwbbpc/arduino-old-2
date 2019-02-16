#ifndef MESSAGETYPETRANSLATOR_H
#define MESSAGETYPETRANSLATOR_H

#include "pb.h"
#include "hasmessages\Header.pb.h"
#include "hasmessages\DiscoverMessage.pb.h"
#include "hasmessages\TemperatureMessage.pb.h"

namespace encoders{
		
	template<class MSGTYPE>
	static HeaderMessage_MessageType getMessageType(){ return HeaderMessage_MessageType_DISCOVER; };
	
	template<>
	inline HeaderMessage_MessageType getMessageType<TemperatureMessage>(){
		return HeaderMessage_MessageType_TEMPERATURE; 
	};

	template<>
	inline HeaderMessage_MessageType getMessageType<DiscoverMessage>(){
		return HeaderMessage_MessageType_DISCOVER; 
	};

	
	template<class MSGTYPE>
	static const pb_field_t* getFields(){return DiscoverMessage_fields};

	template<>
	inline const pb_field_t* getFields<TemperatureMessage>(){
		return TemperatureMessage_fields;
	};

	template<>
	inline const pb_field_t* getFields<DiscoverMessage>(){
		return DiscoverMessage_fields;
	};


}

#endif