#include <queue>

#include "../MyProcess.h"

#ifndef SCHEDULING_ALGORITHM_H
#define SCHEDULING_ALGORITHM_H


class SchedulingAlgorithm {
	public:
		virtual int run(int actual_time, std::queue <Process*> processes) = 0;
};


#endif
