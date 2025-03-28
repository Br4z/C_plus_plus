#include "SchedulingAlgorithm.h"

#ifndef FCFS_H
#define FCFS_H


class FCFS : public SchedulingAlgorithm {
	public:
		FCFS();
		~FCFS();

		int run(int actual_time, std::queue <Process*> processes) override;
};


#endif
