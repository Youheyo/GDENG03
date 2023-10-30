#pragma once
#include "AUIScreen.h"
#include "EngineTime.h"

class EngineProfiler : public AUIScreen{

public:
    EngineProfiler(String name);
    ~EngineProfiler();

    void drawUI() override;

private:

    bool profiler_open = true;
};