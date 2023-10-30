#pragma once
#include <string>
#include "UINames.h"
#include "UIManager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class UIManager;

class AUIScreen{

protected:
    typedef std::string String;
    
    AUIScreen(String name);
    ~AUIScreen();

    std::string getName();
    virtual void drawUI() = 0;

    std::string name;

    friend class UIManager;
};