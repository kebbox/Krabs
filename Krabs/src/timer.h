#pragma once
#include <chrono>
#include <iostream>

//just for the puruse of speed optimization

class Timer {

private:
	std::chrono::time_point< std::chrono::high_resolution_clock> m_startTimePoint;

public:
	Timer() {
		m_startTimePoint =   std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		stop();
	}

	void stop() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << "time took: " << ms << " ms" << std::endl;

	}
};

