#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class Inspector : public AUIScreen{

public:
    Inspector(String name);
    ~Inspector();

    void drawUI() override;

private:

    AGameObject* selectedObject = nullptr;
    bool inspector_open = true;

    float pos_slider_speed = 0.5f;
    float rot_slider_speed = 0.5f;
    float scale_slider_speed = 0.5f;

    float pos[3];
    float rot[3];
    float scale[3];


};