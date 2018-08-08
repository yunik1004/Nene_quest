#ifndef _TIMER_H
#define _TIMER_H

#include <ctime>

class Timer {
private:
	clock_t begin;
	long time;
	bool isStart;
public:
	Timer(void);
	void setTime(long);
	void startTimer(void);
	void unsetTimer(void);
	bool isFinish(void);
};

#endif // !_TIMER_H
