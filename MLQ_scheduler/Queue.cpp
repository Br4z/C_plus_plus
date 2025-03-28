#include "Queue.h"


Queue::Queue() {
	scheduling_algorithm = nullptr;
}

Queue::Queue(SchedulingAlgorithm* scheduling_algorithm) {
	this -> scheduling_algorithm = scheduling_algorithm;
}


void Queue::add_process(Process* process) {
	processes.push(process);
}

int Queue::run(int actual_time) {
	return scheduling_algorithm -> run(actual_time, processes);
}

std::string Queue::to_string() const {
	std::string output = "";
	std::queue <Process*> q = processes;
	while (!q.empty()) {
		output += q.front() -> to_string() + "\n";
		q.pop();
	}

	return output;
}
