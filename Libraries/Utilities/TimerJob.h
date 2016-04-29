#ifndef TIMERJOB_H
#define TIMERJOB_H

#include "../Sensor/ISensor.h"

namespace util{

	struct TimerJob
	{
	public:

		//Constructor
		//! psensor - pointer to the sensor this job is for
		//! periodic - true if this job should be executed on a periodic time, as opposed to one time only
		TimerJob(sensor::ISensor* psensor, bool periodic);

		TimerJob* next;

		bool periodic;
		bool fired;
		sensor::ISensor* sensor;

	};

}

#endif