#include "Timer.h"

using namespace utility;
using namespace time;

Timer::Timer(): begin_(clock_::now()){

}

Timer::~Timer() {
}

//Reset the 0 mark
void Timer::reset() {
	begin_ = clock_::now();
}

//Get time elapsed in seconds
double Timer::elapsed() {
	return std::chrono::duration_cast<second_> (clock_::now() - begin_).count();
}
