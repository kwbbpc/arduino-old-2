#ifndef TIMERBUCKET_H
#define TIMERBUCKET_H

#include "../Sensor/ISensor.h"
#include "MessageBuffer.h"
#include "TimerVector.h"

namespace util{ 

	//! Details
	//! This class contains all the timer logic.  it's required because the arduino has a limited
	//! number of timers to use.  So, the need for multiple timers executing at different intervals
	//! gave rise to this class.  The class maintains one MsTimer2 timer implementation, and sets up
	//! the execution interval as the greatest common denominator of all the timers added to the bucket.
	//! At each execution of the timer, all jobs added to the timer at that specified interval are executed.
	//! The MsTimer2 class is all static, so this class needs some special handling.  It's implemented as
	//! a singleton class, meaning there can only be one instance of it, ever.  The constructor is private
	//! to enforce that.  Instead of constructing it, you just grab the instance of it, which will return
	//! the singleton instance, or create a new one if none exists.
	class TimerBucket
	{

	public:

		//Destructor
		~TimerBucket();

		//Static constructor method to create and return a new timer bucket,
		// or to grab the existing instance of the timer bucket.
		static TimerBucket* getInstance();
		
		//Start the internal timer
		void start();

		//Stop the internal timer
		void stop();

		//Add a sensor to the timer to be fired after a time interval
		//! timerExecutionMs - the time period to fire a single update for this sensor
		//! sensor - the sensor to provide update from
		//! periodic - true if the timer should execute on a periodic basis.  false if
		//!				it should be executed only once at the desired time.
		bool add(unsigned int timerExecutionMs, sensor::ISensor* sensor, bool periodic);

		//Gets data that's available from a sensor that was fired
		sensor::ISensor* getAvailableData();

		//True if data is available to be retrieved from the bucket
		bool isDataAvailable();

		//Processes a new timer fire.  Called from the static fire() method MsTimer2 uses.
		void processTimerFire();

	private:

		//private constructor.  Use the getInstance method to retrieve the bucket instance.
		TimerBucket();

		//update the internal min/max timer bounds
		//timerIntervalMs - the new timer setting to update with
		void updateTimerBounds(unsigned int timerIntervalMs);

		//Gets a vector at the specified timer interval if it exists.
		TimerVector* getVector(unsigned int timerIntervalMs);
		
		//Time ellapsed since the last timer fire (updated every time the timer fires, its assumed to be the previous value + fire interval)
	    unsigned int m_ellapsedTime;

		//The timer fire interval, which is the GCD of all timers added to the bucket
	    unsigned int m_timerFireInterval;

		//The number of timer vectors that are currently in the bucket
	    unsigned int m_timerVectorCount;

		//The smallest timer interval added
	    unsigned int m_minTimer;

		//The largest timer interval added
	    unsigned int m_maxTimer;
		
		//The max number of timer intervals that will be needed.  Arbitrary selection.
		const static unsigned int TimerSlots = 10;
		//An array of timer vectors.  Each timer vector represents all the jobs that need to be executed
		// at a particular interval.  
		TimerVector* m_timerJobs[TimerSlots];

		//Tracks whether the bucket has been initialized or not.  Intialized means that MsTimer2 has been started.
		bool m_initialized;

		//Internal implementation of the buffer.  It's a pointer because
		// something weird was going on during compilation that was initializing
		// the timer bucket when only using the message buffer.
		MessageBuffer<sensor::ISensor>* m_messageBuffer;
				
	};



}


#endif