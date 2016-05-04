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

//Get time elapsed in milliseconds
double Timer::elapsed() {
	return std::chrono::duration_cast<millisecond_> (clock_::now() - begin_).count();
}
