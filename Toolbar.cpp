#include "Toolbar.h"
#include <iostream>
// * Appears at the top of window

Toolbar::Toolbar(String name) : AUIScreen(name) {
}

Toolbar::~Toolbar() {
	
}

void Toolbar::drawUI() {

	if(ImGui::BeginMainMenuBar()){

		if (ImGui::BeginMenu("File")){

				if (ImGui::MenuItem("New", "Ctrl+O")) { std::cout << "New Button Clicked!" << std::endl; }
				if (ImGui::MenuItem("Save", "Ctrl+S"))   { std::cout << "Save Button Clicked!" << std::endl; }
				if (ImGui::MenuItem("Open", "Ctrl+W"))  { std::cout << "Open Button Clicked!" << std::endl; }
				if (ImGui::MenuItem("Exit", "Ctrl+W"))  { toolbar_active = false; }

		ImGui::EndMenu(); // ? End for File Menu
		} 

			if(ImGui::BeginMenu("GameObject")){

				if(ImGui::MenuItem("Create Cube")) {
					GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, nullptr, 0);
				}

				if(ImGui::MenuItem("Create Sphere")) {
					GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, nullptr, 0);
				}

				if(ImGui::MenuItem("Create Plane")) {
					GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, nullptr, 0);
				}

				if(ImGui::BeginMenu("Light")){

					if(ImGui::MenuItem("Point Light")) {
						GameObjectManager::getInstance()->createObject(GameObjectManager::NONE, nullptr, 0);
					}

				ImGui::EndMenu(); // ? End for Light Menu
				}

			ImGui::EndMenu(); // ? End for GameObject Menu
			} 

	ImGui::EndMainMenuBar();

	}

}