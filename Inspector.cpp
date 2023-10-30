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
            pos[0] = this->selectedObject->getPosition().m_x;
            pos[1] = this->selectedObject->getPosition().m_y;
            pos[2] = this->selectedObject->getPosition().m_z;

            rot[0] = this->selectedObject->getRotation().m_x;
            rot[1] = this->selectedObject->getRotation().m_y;
            rot[2] = this->selectedObject->getRotation().m_z;

            scale[0] = this->selectedObject->getScale().m_x;
            scale[1] = this->selectedObject->getScale().m_y;
            scale[2] = this->selectedObject->getScale().m_z;
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
