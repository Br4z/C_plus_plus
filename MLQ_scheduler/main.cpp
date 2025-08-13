#include <iostream>
#include <fstream>
#include <sstream>

#include "MyProcess.h"
#include "MLQScheduler.h"


void load_processes(std::string &filepath, MLQScheduler &MLQ_scheduler) {
	std::ifstream file(filepath);

	if (!file.is_open())
		throw std::runtime_error("Error: failed to open file");

	std::string line;
	while (getline(file, line)) {
		// Skip comment lines and empty lines
		if (line[0] == '#' || line.empty())
			continue;

		std::stringstream ss(line);
		std::string label;
		int burst_time, arrival_time, queue, priority;
		char delimiter;

		std::getline(ss, label, ';');
		ss >> burst_time >> delimiter;
		ss >> arrival_time >> delimiter;
		ss >> queue >> delimiter;
		ss >> priority;

		// Trim any leading/trailing whitespace
		label.erase(0, label.find_first_not_of(" \t\n\r\f\v"));
		label.erase(label.find_last_not_of(" \t\n\r\f\v") + 1);

		MLQ_scheduler.add_process(Process(label, burst_time, arrival_time, queue, priority));
	}

	file.close();
}

void create_output_file(std::string &filepath, MLQScheduler &MLQ_scheduler) {
	std::ofstream file(filepath);
	std::string line;

	if (!file.is_open())
		throw std::runtime_error("Error: failed to open a file");

	// Write a clear header for the output file
	file << "#label;burst;arrival;queue;priority;completion;turnaround;waiting;response\n";


	std::vector <Process> processes = MLQ_scheduler.get_processes();

	if (processes.empty())
		return;

	int processes_length = processes.size();

	int total_waiting_times = 0;
	int total_completion_times = 0;
	int total_response_times = 0;
	int total_turnaround_times = 0;

	for (int i = 0; i < processes_length; i++) {
		Process process = processes[i];
		int waiting_time = process.get_waiting_time();
		int completion_time = process.get_completion_time();
		int response_time = process.get_response_time();
		int turnaround_time = process.get_turnaround_time();
		total_waiting_times += waiting_time;
		total_completion_times += completion_time;
		total_response_times += response_time;
		total_turnaround_times += turnaround_time;

		line += std::to_string(waiting_time) + "; " + std::to_string(completion_time) +
		        " ;" + std::to_string(response_time) + "; " + std::to_string(turnaround_time) + '\n';

		file << line;
	}

	file << "WT = " << std::to_string(total_waiting_times / (double) processes_length)
				<< "; CT = " << std::to_string(total_completion_times / (double) processes_length)
				<< "; RT = " << std::to_string(total_response_times / (double) processes_length)
				<< "; TAT = " << std::to_string(total_response_times / (double) processes_length);
}


int main() {
	MLQScheduler MLQ_scheduler;
	std::string input_filepath = "./input/mlq001.txt";

	load_processes(input_filepath, MLQ_scheduler);
	std::cout << MLQ_scheduler.processes_to_string();
	MLQ_scheduler.assign_processes();
	MLQ_scheduler.run();
	std::cout << "\n\n\n";
	std::cout << MLQ_scheduler.processes_to_string();
	// std::cout << MLQ_scheduler.queues_to_string() << "\n";

	std::string output_filepath = "./output/mlq001.txt";
	create_output_file(output_filepath, MLQ_scheduler);

	return 0;
}
