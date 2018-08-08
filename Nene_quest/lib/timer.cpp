#include "timer.h"

Timer::Timer(void) {
	isStart = false;
}

void Timer::setTime(long ms) {
	time = ms;
	isStart = false;
}

void Timer::startTimer(void) {
	begin = clock();
	isStart = true;
}

void Timer::unsetTimer(void) {
	isStart = false;
}

bool Timer::isFinish(void) {
	if (!isStart) {
		return true;
	}

	clock_t end = clock();
	if (end - begin >= time) {
		return true;
	}

	return false;
}
