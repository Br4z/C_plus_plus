#include "MyProcess.h"


Process::Process(
	const std::string &label,
	int burst_time,
	int arrival_time,
	int queue,
	int priority
)
	: label(label),
	original_burst_time(burst_time),
	burst_time(burst_time),
	arrival_time(arrival_time),
	queue(queue),
	priority(priority)
{ }

const int& Process::get_original_burst_time() const {
	return burst_time;
}

const int& Process::get_burst_time() const {
	return burst_time;
}

const int& Process::get_arrival_time() const {
	return arrival_time;
}

const int& Process::get_queue() const {
	return queue;
}

const int& Process::get_waiting_time() const {
	return waiting_time;
}

const int& Process::get_completion_time() const {
	return completion_time;
}

const int& Process::get_response_time() const {
	return response_time;
}

const int& Process::get_turnaround_time() const {
	return turnaround_time;
}

void Process::set_burst_time(int burst_time) {
	this -> burst_time = burst_time;
}

void Process::set_waiting_time(int waiting_time) {
	this -> waiting_time = waiting_time;
}

void Process::set_completion_time(int completion_time) {
	this -> completion_time = completion_time;
}

void Process::set_response_time(int response_time) {
	this -> response_time = response_time;
}

void Process::set_turnaround_time(int turnaround_time) {
	this -> turnaround_time = turnaround_time;
}

std::string Process::to_string() const {
	return "Process[label=" + label +
			", burst_time=" + std::to_string(burst_time) +
			", arrival_time=" + std::to_string(arrival_time) +
			", priority=" + std::to_string(priority) +
			", waiting_time=" + std::to_string(waiting_time) +
			", completion_time=" + std::to_string(completion_time) +
			", response_time=" + std::to_string(response_time) +
			", turnaround_time=" + std::to_string(turnaround_time) + "]";
}
