#pragma once
#include <chrono>

namespace utility {
namespace time {

//Class to keep track of time elapsed
class Timer{
public:
	Timer();
	~Timer();

	void reset();
	double elapsed();

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;

	std::chrono::time_point<clock_> begin_;
};

}
}
