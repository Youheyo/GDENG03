#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND windowHandle){
    hwnd = windowHandle;
}

UIManager::~UIManager(){
    
}

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle){
    sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy(){

}

void UIManager::drawAllUI(){
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++){
        this->uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}