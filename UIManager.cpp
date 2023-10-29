#include "UIManager.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager::UIManager(HWND windowHandle){
    // * Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	// io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// * Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirect3DDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

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
    
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
    
    delete sharedInstance;
}

void UIManager::addUI(AUIScreen* ui)
{
    sharedInstance->uiList.push_back(ui);
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++){
        this->uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}