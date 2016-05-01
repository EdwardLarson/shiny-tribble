#include "Timer.h"

using namespace utility;
using namespace time;

Timer::Timer(): begin_(clock_::now()){

}

Timer::~Timer() {
}


void Timer::reset() {
	begin_ = clock_::now();
}

double Timer::elapsed() {
	return std::chrono::duration_cast<second_> (clock_::now() - begin_).count();
}
