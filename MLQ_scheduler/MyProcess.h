#include <string>

#ifndef MY_PROCESS_H
#define MY_PROCESS_H


class Process {
	private:
		std::string label;
		int burst_time;
		int arrival_time;
		int queue;
		int priority;
		int waiting_time = 0;
		int completion_time = 0;
		int response_time = 0;
		int turnaround_time = 0;
	public:
		Process(
					const std::string &label,
					int burst_time,
					int arrival_time,
					int queue,
					int priority
				);

		int get_burst_time() const;
		int get_arrival_time() const;
		int get_queue() const;
		int get_waiting_time() const;
		int get_completion_time() const;
		int get_response_time() const;
		int get_turnaround_time() const;

		void set_burst_time(int burst_time);
		void set_waiting_time(int waiting_time);
		void set_completion_time(int completion_time);
		void set_response_time(int response_time);
		void set_turnaround_time(int turnaround_time);

		std::string to_string() const;
};


#endif
