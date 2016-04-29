
#include "TimerBucket.h"
#include "MessageBuffer.h"

#include "../MsTimer2/MsTimer2.h"

#include <Arduino.h>


namespace {

	//The static singleton instance of the timer bucket
	static util::TimerBucket* m_TimerBucketInstance = 0;

	//! The main timer fire function.  Execution must be as fast as possible
	//! in here, and absolutely no serial.print'ing
	static void fire()
	{
		//get the instance to the timer
		util::TimerBucket* bucket = util::TimerBucket::getInstance();

		//fire the appropriate timers
		bucket->processTimerFire();
	}

}

namespace util{



	void TimerBucket::processTimerFire()
	{

		//increment the time ellapsed, since the timer was fired on the interval
		m_ellapsedTime += m_timerFireInterval;

		for(int i=0; i<=m_timerVectorCount; ++i)
		{
			//fire if this is a multiple of the timer
			if(m_ellapsedTime % m_timerJobs[i]->m_timerMs == 0)
			{
				//fire this timer vector's jobs, it's a multiple of the current time ellapsed.
				//Serial.print("FiredVec"); Serial.println(i);
				m_timerJobs[i]->fire();
			}
		}

		//reset the ellapsed time if it exceeds the largest fire interval
		if(m_ellapsedTime >= m_maxTimer)
		{
			m_ellapsedTime=0;
		}

	}


	TimerBucket* TimerBucket::getInstance()
	{
		if(!m_TimerBucketInstance)
		{
			m_TimerBucketInstance = new TimerBucket();
		}

		return m_TimerBucketInstance;

	}

	TimerBucket::TimerBucket():
	m_ellapsedTime(0),
		m_timerFireInterval(0),
		m_timerVectorCount(0),
		m_minTimer(65535),
		m_maxTimer(0),
		m_messageBuffer(0),
		m_initialized(false)
	{
		//Serial.print("m_timerVectorCount:"); Serial.println(m_timerVectorCount);
		m_messageBuffer = new MessageBuffer<sensor::ISensor>(20);
	}

	TimerBucket::~TimerBucket()
	{
		delete m_messageBuffer;
		delete[] m_timerJobs;
	}


	void TimerBucket::stop()
	{
		MsTimer2::stop();
	}



	void TimerBucket::start()
	{
		//Serial.print("Start called.  Initalized: "); Serial.println(m_initialized);
		if(!m_initialized)
		{
			unsigned int interval = 0;
			//find the greatest common denominator by starting with the smallest timer segment
			// and decreasing the value in an attempt to find the greatest common denominator
			//	to use for the timer interval
			for(int i=m_minTimer; i>0; --i)
			{
				for(int j=0; j<m_timerVectorCount; ++j)
				{
					//check for GCD with modulus
					if(m_timerJobs[j]->m_timerMs % i != 0)
					{
						interval = 0;
						break;
					}
					else
					{
						interval = i;
					}
				}
				//check if an interval was found
				if(interval != 0)
				{
					//interval found, use it
					break;
				}
			}

			m_timerFireInterval = interval;
			m_initialized = true;

			MsTimer2::set(m_timerFireInterval, &fire);
		}

		//Serial.print("Starting timer at fire interval "); Serial.println(m_timerFireInterval);
		MsTimer2::start();


	}

	void TimerBucket::updateTimerBounds(unsigned int timerIntervalMs)
	{
		if(timerIntervalMs < m_minTimer)
		{
			m_minTimer = timerIntervalMs;
		}
		if(timerIntervalMs > m_maxTimer)
		{
			m_maxTimer = timerIntervalMs;
		}
	}

	TimerVector* TimerBucket::getVector(unsigned int timerIntervalMs)
	{
		//check if the timer exists already
		for(int i=0; i<m_timerVectorCount; ++i)
		{
			if(m_timerJobs[i]->m_timerMs == timerIntervalMs)
			{
				return m_timerJobs[i];
			}
		}

		//the timer vector for this interval wasn't found.
		return 0;
	}


	bool TimerBucket::add(unsigned int timerIntervalMs, sensor::ISensor* sensor, bool periodic)
	{
		m_initialized = false;

		if(timerIntervalMs > 65535)
		{
			//interval is too large to add the sensor
			return false;
		}

		updateTimerBounds(timerIntervalMs);

		//Get the vector with this timer execution if it already exists
		TimerVector* vec = getVector(timerIntervalMs);

		if(vec)
		{
			//add the sensor to the existing vector
			vec->add(sensor, periodic);
		}
		else
		{
			//create a new vector and add it
			//Serial.print("Making new vector at index "); Serial.println(m_timerVectorCount);
			m_timerJobs[m_timerVectorCount] = new TimerVector(m_messageBuffer, timerIntervalMs);
			//Serial.print("Vector count:"); Serial.println(vectorCount);
			m_timerJobs[m_timerVectorCount]->add(sensor, periodic);

			//increment the internal index of timer vectors
			++m_timerVectorCount;

		}


		//Serial.println("done adding.");
		//Serial.print("timerCount:"); Serial.println(m_timerVectorCount);
		//Serial.println();Serial.println();

		return true;

	}

	bool TimerBucket::isDataAvailable()
	{
		return m_messageBuffer->hasData();
	}

	sensor::ISensor* TimerBucket::getAvailableData()
	{
		if(m_messageBuffer->hasData())
		{
			return m_messageBuffer->getNext();
		}

		//let vectors cleanup any old jobs
		for(int i = 0; i < m_timerVectorCount; ++i)
		{
			m_timerJobs[i]->cleanupFiredJobs();
		}

		return 0;
	}

}