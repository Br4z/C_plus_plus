#include "SchedulingAlgorithm.h"

#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H


class RoundRobin : public SchedulingAlgorithm {
	private:
		int time_quantum;
	public:
		RoundRobin(int time_quantum);
		~RoundRobin();

		int run(int actual_time, std::queue <Process*> processes) override;
};


#endif
