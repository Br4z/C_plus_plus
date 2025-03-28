#include "scheduling_algorithm/RoundRobin.h"
#include "scheduling_algorithm/FCFS.h"
#include "MLQScheduler.h"


MLQScheduler::MLQScheduler() {
	queues.resize(3);

	RoundRobin* RR_1 = new RoundRobin(3);
	Queue RR_1_queue = Queue(RR_1);
	queues[0] = RR_1_queue;

	RoundRobin* RR_2 = new RoundRobin(5);
	Queue RR_2_queue = Queue(RR_2);
	queues[1] = RR_2_queue;

	FCFS* FCFS_ = new FCFS();
	Queue FCFS_queue = Queue(FCFS_);
	queues[2] = FCFS_queue;
}


std::vector <Process> MLQScheduler::get_processes() {
	return processes;
}

void MLQScheduler::run() {
	int actual_time = 0;

	int RR_1_time = queues[0].run(actual_time);
	actual_time += RR_1_time;

	int RR_2_time = queues[1].run(actual_time);
	actual_time += RR_2_time;

	int FCFS_time = queues[2].run(actual_time);
	actual_time += FCFS_time;
}

void MLQScheduler::add_process(Process process) {
	processes.push_back(process);
}

void MLQScheduler::assign_processes() {
	int processes_legth = processes.size();

	for (int i = 0; i < processes_legth; i++) {
		Process* process = &processes[i];

		queues[process -> get_queue() - 1].add_process(process);
	}
}

std::string MLQScheduler::processes_to_string() const {
	std::string output = "";

	for (Process process : processes)
		output += process.to_string() + '\n';

	return output;
}

std::string MLQScheduler::queues_to_string() const {
	std::string output = "";

	for (unsigned long long i = 0; i < queues.size(); i++) {
		output += "Queue " + std::to_string(i + 1) + ":\n";
		output += queues[i].to_string();
		output += "\n";
	}
	return output;
}
