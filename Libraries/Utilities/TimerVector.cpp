#include "TimerVector.h"	
//#include <Arduino.h>

namespace util{


	TimerVector::TimerVector(MessageBuffer<sensor::ISensor>* buffer, int timerMs):
	m_buffer(buffer),
		m_timerMs(timerMs),
		m_jobs(0)
	{
		//Serial.print("New Timer Vector created for ");
		//Serial.println(timerMs);
		clear();
	}

	void TimerVector::clear()
	{
		TimerJob* iter = m_jobs;
		while(iter != 0)
		{
			//save the next result
			TimerJob* pTempNext = iter->next;
			//cleanup
			delete iter;
			//go to next
			iter = pTempNext;
		}

		//reset the head pointer to 0
		m_jobs=0;

	}

	//adds a sensor to this timer vector
	void TimerVector::add(sensor::ISensor* sensor, bool periodic)
	{

		//Serial.print("Adding new sensor "); Serial.println((int)sensor);

		TimerJob* jobToAdd = 0;

		if(m_jobs)
		{
			TimerJob* iter = m_jobs;
		
			//go to the end of the list
			while(iter->next != 0)
			{
				iter = iter->next;
			}

			TimerJob* pNewJob = new TimerJob(sensor, periodic);
			iter->next = pNewJob;
			
		}
		else
		{
			//need to setup the head
			m_jobs = new TimerJob(sensor, periodic);
		}
		
		/*debug statements
		Serial.print("New addition to vector "); Serial.print((int)this); Serial.print(": ");
			TimerJob* iter = m_jobs;
			while(iter != 0)
			{
				Serial.print((int)iter->sensor); Serial.print(",");
				iter = iter->next;
			}
			Serial.println();
			*/
		//Serial.print("Count = ");
		//Serial.println(m_count);

	}


	//this method was brought outside of fire() because apparently it takes too long to execute inside the ISR.
	void TimerVector::cleanupFiredJobs()
	{
		
		TimerJob* iter = m_jobs;
		TimerJob* prev = m_jobs;
		while(iter != 0)
		{
			if(iter->fired && !iter->periodic)
			{
				//remove the job from the list
				if(prev != iter)
				{
					prev->next = iter->next;
					//cleanup
					delete iter;
					iter = prev->next;
				}
				else
				{
					//if there wasn't a previous node, the next one is the new head
					m_jobs = iter->next;
					//cleanup
					delete iter;
					//assign the next iter
					iter = m_jobs;
					prev = m_jobs;
				}

			}
			else
			{
				iter = iter->next;
			}
			
		}
			

	}

	//fires all sensors in this vector
	void TimerVector::fire()
	{
		//Serial.println("fired");
		TimerJob* iter = m_jobs;
		TimerJob* prev = iter;
		while(iter != 0)
		{
			//check if the job should be added (if it's not periodic and has already been fired, don't add.)
			if((!iter->periodic && !iter->fired) || iter->periodic)
			{
				m_buffer->add(iter->sensor);
				iter->fired = true;
				//Serial.print("Added "); Serial.println((int)iter->sensor);
			}
			
			//go to next
			iter = iter->next;
			
		}

		//Serial.println("done");
	}

	int TimerVector::size()
	{
		int count = 0;
		TimerJob* iter = m_jobs;
		while(iter != 0)
		{
			count++;
			iter = m_jobs->next;
		}

		return count;
	}
	
}