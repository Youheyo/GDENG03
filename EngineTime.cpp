#include "EngineTime.h"

void EngineTime::initialize()
{
	static EngineTime engineTime;
}

double EngineTime::getDeltaTime()
{
	sharedInstance->deltaTime = sharedInstance->end - sharedInstance->start;
	return sharedInstance->deltaTime;
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
