#include "FCFS.h"


FCFS::FCFS() {

}

FCFS::~FCFS() {

}

int FCFS::run(int actual_time, std::queue <Process*>& processes) {
	while (!processes.empty()) {
		Process* current_process = processes.front();
		processes.pop();

		// Account for CPU idle time if the process has not arrived yet
		actual_time = std::max(actual_time, current_process -> get_arrival_time());

		actual_time += current_process -> get_burst_time();
		current_process -> set_burst_time(0);
		current_process -> set_completion_time(actual_time);
		current_process -> set_turnaround_time(current_process -> get_completion_time() -
												current_process -> get_arrival_time());
		current_process -> set_waiting_time(current_process -> get_turnaround_time() -
												current_process -> get_original_burst_time());
		current_process -> set_response_time(current_process -> get_waiting_time());
	}

	return actual_time;
}
