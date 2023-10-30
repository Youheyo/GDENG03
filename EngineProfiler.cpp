#include "EngineProfiler.h"
#include <cmath>

EngineProfiler::EngineProfiler(String name) : AUIScreen(name) {
    
}

EngineProfiler::~EngineProfiler() {
    
}

void EngineProfiler::drawUI() {

    if(ImGui::Begin("Profiler", &profiler_open)){
        
        // String ms_text = "Application Average " + std::to_string(1000 * EngineTime::getDeltaTime()) + " ms/frame (" + std::to_string(std::round(1 / EngineTime::getDeltaTime()))  + " FPS)";
        String ms_text = "Application Average " + std::to_string(ImGui::GetIO().Framerate / 1000.0f) + " ms/frame (" + std::to_string(ImGui::GetIO().Framerate)  + " FPS)";
        ImGui::Text(ms_text.c_str());

    ImGui::End();
    }
}
