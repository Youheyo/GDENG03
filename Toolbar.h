#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class Toolbar : public AUIScreen{

public:
    Toolbar(String name, bool* wireMode);
    ~Toolbar();

    void drawUI() override;
    
private:

    String name;
    bool toolbar_active = true;
    bool* rendermode;

};