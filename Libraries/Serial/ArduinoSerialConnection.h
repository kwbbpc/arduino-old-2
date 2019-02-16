#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include "ISerialConnection.h"

namespace serial{

	class ArduinoSerialConnection : public ISerialConnection
	{
	public:
	
		ArduinoSerialConnection();
	
		//See ISerialConnection
		virtual void write(const uint8_t* buffer, uint16_t bufferSize);
		virtual int read(uint8_t* buffer, uint16_t bufferSize);
		
	private:



	};

}

#endif