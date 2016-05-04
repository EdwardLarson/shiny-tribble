#pragma once
#include <chrono>

namespace utility {
namespace time {

//Class to keep track of time elapsed since a 0 mark
class Timer{
public:
	Timer();
	~Timer();

	void reset();
	double elapsed();

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::milli > millisecond_;

	std::chrono::time_point<clock_> begin_;
};

}
}
