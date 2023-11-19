#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class Toolbar : public AUIScreen{

public:
    Toolbar(String name, bool* wireMode);
    ~Toolbar();

    void drawUI() override;
    
    void spawnPhysicsCubes(int amt = 50);

private:

    String name;
    bool toolbar_active = true;
    bool* rendermode;

};