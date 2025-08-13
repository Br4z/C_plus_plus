#include <string>

#ifndef MY_PROCESS_H
#define MY_PROCESS_H


class Process {
	private:
		std::string label;
		int original_burst_time;
		int burst_time;
		int arrival_time;
		int queue;
		int priority;
		int waiting_time = -1;
		int completion_time = -1;
		int response_time = -1;
		int turnaround_time = -1;
	public:
		Process(
					const std::string &label,
					int burst_time,
					int arrival_time,
					int queue,
					int priority
				);

		const int& get_original_burst_time() const;
		const int& get_burst_time() const;
		const int& get_arrival_time() const;
		const int& get_queue() const;
		const int& get_waiting_time() const;
		const int& get_completion_time() const;
		const int& get_response_time() const;
		const int& get_turnaround_time() const;

		void set_burst_time(int burst_time);
		void set_waiting_time(int waiting_time);
		void set_completion_time(int completion_time);
		void set_response_time(int response_time);
		void set_turnaround_time(int turnaround_time);

		std::string to_string() const;
};


#endif
