#include "RoundRobin.h"


RoundRobin::RoundRobin(int time_quantum) : time_quantum(time_quantum) { }

RoundRobin::~RoundRobin() {

}

int RoundRobin::run(int actual_time, std::queue <Process*>& processes) {
	while (!processes.empty()) {
		Process* current_process = processes.front();
		processes.pop();

		// Account for CPU idle time if the process has not arrived yet
		actual_time = std::max(actual_time, current_process -> get_arrival_time());

		if (current_process -> get_response_time() == -1 && current_process -> get_arrival_time() <= actual_time)
			current_process -> set_response_time(actual_time - current_process -> get_arrival_time());

		int remaining_burst = current_process -> get_burst_time();

		if (remaining_burst > time_quantum) {
			// Process runs for a full quantum and is then re-queued.
			actual_time += time_quantum;
			current_process -> set_burst_time(remaining_burst - time_quantum);
			processes.push(current_process);
		} else {
			actual_time += remaining_burst;
			current_process -> set_burst_time(0);
			current_process -> set_completion_time(actual_time);
			current_process -> set_turnaround_time(current_process -> get_completion_time() -
			                                        current_process -> get_arrival_time());
			current_process -> set_waiting_time(current_process -> get_turnaround_time() -
			                                    current_process -> get_original_burst_time());
		}
	}
	return actual_time;
}
