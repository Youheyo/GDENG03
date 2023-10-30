#pragma once
#include "AUIScreen.h"
#include "GameObject.h";
#include "GameObjectManager.h";


class SceneOutline : public AUIScreen{

public:

    SceneOutline(String name);
    ~SceneOutline();

    void drawUI() override;

    void updateObjectList();

private:

    std::vector<GameObject*> obj_list;

    bool scene_outline_open = true;

    int object_count = 0;
};