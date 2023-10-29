#include "Toolbar.h"
// * Appears at the top of window

Toolbar::Toolbar(String name) : AUIScreen(name) {

}

Toolbar::~Toolbar() {
    
}

void Toolbar::drawUI() {
    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("Menu", &toolbar_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Open", "Ctrl+W"))  { /* Do stuff */ }
            if (ImGui::MenuItem("Exit", "Ctrl+W"))  { toolbar_active = false; }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("GameObject")){
            if(ImGui::MenuItem("Create Cube")) {
                GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, nullptr, 0);
            };
            if(ImGui::MenuItem("Create Sphere")) {
                GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, nullptr, 0);
            };
            if(ImGui::MenuItem("Create Plane")) {
                GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, nullptr, 0);
            };
            if(ImGui::MenuItem("Create Light")) {};
        }
        ImGui::EndMenuBar();
    }
    ImGui::End();    
}
