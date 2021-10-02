#pragma once

#include <Windows.h>

class TimerClass
{
private:
	double countsPerSecond;
	__int64 CounterStart, frameTimeOld;
	int frameCount, fps;
public:
	TimerClass();
	TimerClass(const TimerClass&);
	~TimerClass();

	void CountFrames();
	void StartTimer();
	double GetTime();
	double GetFrameTime();
	
};

