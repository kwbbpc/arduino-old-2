#ifndef TIMERVECTOR_H
#define TIMERVECTOR_H

#include "../Sensor/ISensor.h"
#include "MessageBuffer.h"
#include "TimerJob.h"


namespace util{

	//! Deatils
	//! This class is a container that the TimerBucket uses.  This class holds a number of jobs that need to be
	//! executed at a specific interval.  All the timer logic is handled in the Bucket class.  This class
	//! just holds the jobs to be executed, and what time interval they should be executed at.
	struct TimerVector
	{

	//! Constructor
	//! buffer - a pointer to the message buffer to use to insert new messages into.  This is required
	//!				because messages are inserted during an interrupt routine, which needs to be lightning
	//!				fast or the ardy will crash without telling you why.
	//! timerMs - the timer interval this vector holds jobs for.  Timers aren't handled here, it's just for informational purposes.
		TimerVector(MessageBuffer<sensor::ISensor>* buffer, int timerMs);

		//clear out all sensors from this vector
		void clear();

		//gets the current size of the vector
		int size();

		//adds a sensor to this timer vector
		//! sensor - the sensor to add
		//! periodic - true if this should be executed on a periodic schedule, false if it's just a one shot
		void add(sensor::ISensor* sensor, bool periodic);

		//fires all sensors in this vector
		void fire();

		//this method was brought outside of fire() because apparently it takes too long to execute inside the ISR.
		void cleanupFiredJobs();
				
		//the timer value
		int m_timerMs;
		
		//the sensors to fire, in a linked list of timer jobs
		TimerJob* m_jobs;

		//Pointer to the message buffer to append messages into
		MessageBuffer<sensor::ISensor>* m_buffer;


	};

}
#endif