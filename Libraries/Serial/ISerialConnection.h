#ifndef ISERIALCONNECTION_H
#define ISERIALCONNECTION_H

#include <stdint.h>


namespace serial{

	class ISerialConnection
	{

	public:

		static const uint16_t ReadBufferSize = 512;

		//Writes a buffer to the serial port
		//! buffer - the buffer to write
		//! bufferSize - the size of the buffer
		virtual void write(const uint8_t* buffer, uint16_t bufferSize) = 0;

		//Reads from the serial and stores the message into the buffer with the given max size
		virtual int read(uint8_t* buffer, uint16_t maxBufferSize) = 0;
	};


}

#endif