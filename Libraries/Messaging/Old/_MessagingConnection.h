#ifndef MESSAGINGCONNECTION_H
#define MESSAGINGCONNECTION_H

#include "IMessageRouter.h"
#include "../NanoPB/hasmessages/Header.pb.h"
#include "../Encoders/NanoPbCodec.h"

namespace messaging{

	class MessagingConnection
	{
	private:
		LogisticsInfo m_sourceLogistics;
		IMessageRouter* m_router;

	public:

		MessagingConnection(const char* platformGuid, const char* sensorGuid, IMessageRouter* router);
		~MessagingConnection();

		template<class MSGTYPE>
		bool sendMessage(const MSGTYPE& message)
		{
			return sendMessage(0, message);
		};

		template<class MSGTYPE>
		bool sendMessage(const LogisticsInfo* destination, const MSGTYPE& message)
		{
			uint8_t* buffer = 0;
			uint16_t bufferSize;

			bool encoded = encoders::nanopb::encodeMessage<MSGTYPE>(&m_sourceLogistics, 0, &message, &buffer, bufferSize);

			if(encoded)
			{
				m_router->sendMessage(buffer,bufferSize);
			}

			return encoded;
		};

		
	};

}

#endif