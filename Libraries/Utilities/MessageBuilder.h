#ifndef MESSAGEBUILDER_H
#define MESSAGEBUILDER_H

#include <stdint.h>


namespace util{

	class MessageBuilder
	{

	public:

		//! Constructor
		//! messageSize - the total size to allocate for the internal message (size upon completion)
		MessageBuilder(int messageSize);

		//! Default Constructor
		MessageBuilder();

		//! Post construction initializer, used with default constructor
		//! messageSize - the total size to allocate for the internal message (size upon completion)
		void init(int messageSize);

		~MessageBuilder();

		//! Gets the internal message buffer
		uint8_t* get();

		//! Performs a deep copy of the internal message into the destination buffer passed in
		bool MessageBuilder::deepCopy(uint8_t** destination);

		//! Gets the size of the internal message
		int sizeOf();

		//! appends a message to the internal buffer
		//! origin - 
		void append(const uint8_t* origin, int indexBegin, int indexEnd);

	private:

		uint8_t* internalMessage;
		int internalIndex;


	};

}

#endif

