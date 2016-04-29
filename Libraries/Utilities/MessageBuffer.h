#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H


namespace util{

	template <class T>
	struct MessageBufferUnit
	{
		T* buffer;
		int length;

		//Destructor to automatically ensure that the internal
		//	array buffer is deleted when the unit destructs.
		~MessageBufferUnit()
		{
			delete[] buffer;
		}
	};

	//! Details
	//! This class is a basic implementation of a circular buffer.  It's used to hold onto messages
	//! that need to be processed, but can't be processed at the time of execution.  Messages are
	//! added to the buffer with add(), and retrieved by getNext().  Memory management of the added
	//! or removed items is left up to the caller, and isn't handled here.
	template <class T>
	class MessageBuffer
	{

	public:

		//! Constructor
		//! bufferSize - the number of slots to use in the circular buffer
		MessageBuffer(int bufferSize):
		m_getIndex(0),
		m_putIndex(0),
		m_bufferSize(bufferSize),
		count(0),
		m_dataArray(new T*[bufferSize])
		{
			//Don't call serial.print if you're constructing this in global space in a sketch, before Serial is setup!
			//Serial.print("Constructor called.");
			//Serial.print("Initializing message buffer with size of "); Serial.println(m_bufferSize);
			for(int i=0; i<m_bufferSize; ++i)
			{
				m_dataArray[i] = 0;
			}
		}

		//! Destructor, just for compelteness.
		~MessageBuffer()
		{
			delete[] m_dataArray;
		}

		//Adds an item to the buffer.  Returns true if the add was successful, false if the item overflowed
		//	and wasn't added.  If the item wasn't added, make sure you clean it up or you'll leak memory.
		bool add(T* sensor)
		{
			if(m_dataArray[m_putIndex] == 0)
			{
				m_dataArray[m_putIndex] = sensor;
				++m_putIndex;
				if(m_putIndex >= m_bufferSize)
				{
					m_putIndex = 0;
				}
				++count;
				
				return true;
			}
			return false;
		}

		//! Returns the next item out of the buffer.
		T* getNext()
		{
			T* toReturn = m_dataArray[m_getIndex];
		
			//only increment if data was found
			if(toReturn)
			{
				//free the space
				m_dataArray[m_getIndex] = 0;

				++m_getIndex;
				//test for rollover
				if(m_getIndex >= m_bufferSize)
				{
					m_getIndex = 0;
				}
				--count;
			
			}

			return toReturn;
		}

		//!Determines if there's data available in the buffer.
		virtual bool hasData()
		{
			return (count > 0);
		}


		
	
	private:
		T** m_dataArray;
		int m_bufferSize;
		int m_getIndex;
		int m_putIndex;
		int count;
		
	};

}
#endif