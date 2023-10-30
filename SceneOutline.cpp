#include "SceneOutline.h"

SceneOutline::SceneOutline(String name) : AUIScreen(name) {
    
}

SceneOutline::~SceneOutline() {
    
}

void SceneOutline::drawUI() {

    updateObjectList();

    if(ImGui::Begin("Scene Outliner", &scene_outline_open, ImGuiWindowFlags_AlwaysVerticalScrollbar)){

        // * Object Button Loop
        for(int i = 0; i < this->obj_list.size(); i++){

            if(ImGui::Button(this->obj_list[i]->getName().c_str())){
                GameObjectManager::getInstance()->setSelectedObject(this->obj_list[i]);
            }

        }
        // * End of Loop


    ImGui::End();
    }
}

void SceneOutline::updateObjectList()
{
    this->obj_list = GameObjectManager::getInstance()->getAllObjects();

}
