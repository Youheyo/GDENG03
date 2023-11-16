#include "Inspector.h"


Inspector::Inspector(String name) : AUIScreen(name){
    
}

Inspector::~Inspector() {
    
}

void Inspector::drawUI() {
    this->selectedObject = GameObjectManager::getInstance()->getSelectedObject();

    if(ImGui::Begin("Inspector", &inspector_open, ImGuiWindowFlags_AlwaysVerticalScrollbar)){

        // ? Check if Selected object is null
        if(this->selectedObject == nullptr){ 
            ImGui::Text("No object is currently selected. Select an object on the Scene");
        }
        else{
            String selectText = "Current Object: " + this->selectedObject->getName();
            ImGui::Text(selectText.c_str());

            bool objectEnable =  this->selectedObject->isEnabled();
            ImGui::Checkbox("Enabled", &objectEnable);
            this->selectedObject->setEnabled(objectEnable);

#pragma region Object param Getting
            pos[0] = this->selectedObject->getPosition().getX();
            pos[1] = this->selectedObject->getPosition().getY();
            pos[2] = this->selectedObject->getPosition().getZ();

            rot[0] = this->selectedObject->getRotation().getX();
            rot[1] = this->selectedObject->getRotation().getY();
            rot[2] = this->selectedObject->getRotation().getZ();

            scale[0] = this->selectedObject->getScale().getX();
            scale[1] = this->selectedObject->getScale().getY();
            scale[2] = this->selectedObject->getScale().getZ();
#pragma endregion
            
            ImGui::DragFloat3("Position", pos, pos_slider_speed);
            ImGui::DragFloat3("Rotation", rot, rot_slider_speed);
            ImGui::DragFloat3("Scale", scale, scale_slider_speed);

#pragma region Object Param Setting

        this->selectedObject->setPosition(pos[0], pos[1], pos[2]);
        this->selectedObject->setRotation(rot[0], rot[1], rot[2]);
        this->selectedObject->setScale(scale[0], scale[1], scale[2]);

#pragma endregion

        }

    ImGui::End();
    }

}
