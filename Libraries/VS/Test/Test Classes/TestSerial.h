#ifndef TESTSERIAL_H
#define TESTSERIAL_H

#include "Serial/ISerialConnection.h"

#include <vector>
#include <utility>
#include <cstdint>


namespace serial{ namespace test{

	class TestSerial : public ISerialConnection
	{

	public: 

		//input parameters
		virtual void write(const uint8_t* buffer, uint16_t bufferSize);

		//output parameters
		virtual int read(uint8_t* buffer, uint16_t bufferSize);

		typedef std::pair<const uint8_t*, uint16_t> Message;
		std::vector<Message> writtenMessages;
		std::vector<Message> readMessages;

	};

}}

#endif