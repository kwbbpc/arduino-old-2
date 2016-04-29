
#include "ArduinoSerialConnection.h"
#include <Arduino.h>

/*
template<class T>
T* concat(T* buffer1, uint32_t buffer1Size, T* buffer2, uint32_t buffer2Size)
{
	T returnBuffer[buffer1Size + buffer2Size];
	uint32_t returnBufferSize = buffer1Size + buffer2Size;
	for(int i=0; i<buffer1Size; ++i)
	{
		returnBuffer[i] = buffer1[i];
	}
	for(int i=0; i<buffer2Size; ++i)
	{
		returnBuffer[buffer1Size + i] = buffer2[i];
	}

	return returnBuffer;
}*/

namespace serial{


		ArduinoSerialConnection::ArduinoSerialConnection()
		{
		}
		
		//See ISerialConnection
		void ArduinoSerialConnection::write(const uint8_t* buffer, uint16_t bufferSize)
		{
			for(int i=0; i<bufferSize; ++i)
			{
				Serial.write(buffer[i]);
			}
		}
		
		int ArduinoSerialConnection::read(uint8_t* buffer, uint16_t maxBufferSize)
		{
			int i = 0;
			while(Serial.available() > 0)
			{
				buffer[i] = Serial.read();
				++i;

				if (i == maxBufferSize)
					return 0;	//bail out, the message is too big.

				/*
				if(i == ReadBufferSize)
				{
					//a buffer overflow occurred while reading.
					uint8_t buffer2[ReadBufferSize];
					uint16_t buffer2Size;
					//recursively call read with a new buffer to hold the extra data until there isn't any more to read
					read(buffer2, buffer2Size);

					//append all the arrays together
					buffer = concat(buffer, ReadBufferSize, buffer2, buffer2Size);
				}*/
					
					
			}

			return i;



		}



	}
