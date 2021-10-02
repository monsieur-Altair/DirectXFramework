#include "TimerClass.h"

TimerClass::TimerClass()
{
	countsPerSecond = 0;
	CounterStart = 0;
	frameTimeOld = 0;
	frameCount = 0;
	fps=0;
}

TimerClass::TimerClass(const TimerClass& obj)
{

}

TimerClass::~TimerClass()
{

}

void TimerClass::CountFrames()
{
	frameCount++;
	if (this->GetTime() > 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		this->StartTimer();
	}
}

void TimerClass::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

double TimerClass::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

double TimerClass::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / countsPerSecond;
}