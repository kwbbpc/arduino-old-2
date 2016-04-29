
#include "TimerJob.h"



namespace util{



	//Constructor
	TimerJob::TimerJob(sensor::ISensor* psensor, bool bperiodic)
	{
		next = 0;
		sensor = psensor;
		periodic = bperiodic;

		//initialize the fired to false, because it hasn't been fired yet.
		fired = false;


	}


	

}