#ifndef MESSAGEROUTER_H
#define MESSAGEROUTER_H

#include "../Sensor/ISensor.h"
#include "../NanoPB/pb.h"
#include "../Serial/ISerialConnection.h"
#include "IParser.h"
#include "IMessageRouter.h"
#include "../Utilities/LinkedList.h"


namespace messaging{

	class MessageRouter : public IMessageRouter
	{
	public:
		
		MessageRouter(serial::ISerialConnection* serial);
		~MessageRouter();

		//Interface methods, see IMessageRouter
		virtual void routeMessage(uint8_t* buffer, int bufferSize);
		virtual void registerParser(IParser* parser);
		virtual void sendMessage(IParser::ParserType::Enum type, uint8_t* buffer, int bufferSize);

	private:
		
		serial::ISerialConnection* m_serial;
		LinkedList<IParser*> m_parsers;

	};

}

#endif