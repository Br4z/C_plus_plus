#include "RoundRobin.h"


RoundRobin::RoundRobin(int time_quantum) {
	this -> time_quantum = time_quantum;
}

RoundRobin::~RoundRobin() {

}


int RoundRobin::run(int actual_time, std::queue <Process*> processes) {
	while (!processes.empty()) {
		Process* current_process = processes.front();
		processes.pop();

		if (current_process -> get_response_time() == 0 && current_process -> get_arrival_time() <= actual_time)
			current_process -> set_response_time(actual_time - current_process -> get_arrival_time());

		if (current_process -> get_burst_time() > time_quantum) {
			actual_time += time_quantum;
			current_process -> set_burst_time(current_process -> get_burst_time() - time_quantum);
			processes.push(current_process);
		} else {
			actual_time += current_process -> get_burst_time();
			current_process -> set_burst_time(0);
			current_process -> set_completion_time(actual_time);
			current_process -> set_turnaround_time(current_process -> get_completion_time() -
													current_process -> get_arrival_time());
			current_process -> set_waiting_time(current_process -> get_turnaround_time() -
												(current_process -> get_burst_time() + current_process -> get_response_time()));
		}
	}

	return actual_time;
}