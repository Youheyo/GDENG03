#include "Toolbar.h"
#include <iostream>
#include "SceneCameraHandler.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
// * Appears at the top of window

Toolbar::Toolbar(String name, bool* wiremode) : AUIScreen(name) {
	rendermode = wiremode;
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

			if(ImGui::BeginMenu("Physics Object")){
				if(ImGui::MenuItem("Create Physics Cube")){
					spawnPhysicsCubes(10);
				}
			if(ImGui::MenuItem("Create Physics Plane")){
				GameObjectManager* manager = GameObjectManager::getInstance();
					// manager->createObject(GameObjectManager::PLANE, nullptr, 0);
					manager->createObject(GameObjectManager::CUBE, nullptr, 0);
					manager->getSelectedObject()->setPosition(0,-5,0);
					manager->getSelectedObject()->setScale(64,0.1,64);

					PhysicsComponent* physComponent = new PhysicsComponent("PhysComp Plane", manager->getSelectedObject());
					physComponent->getRigidBody()->setType(BodyType::STATIC);
				}
			ImGui::EndMenu();
			}
			
			if (ImGui::BeginMenu("View Modes"))
			{
				ImGui::SeparatorText("Projection Modes"); // view/projection modes
				if (ImGui::MenuItem("Perspective View"))
				{
					SceneCameraHandler::getInstance()->getSceneCamera()->setPerspectiveView();
					std::cout << "Projection mode: PERSPECTIVE VIEW\n";
				}
				if (ImGui::MenuItem("Topdown View"))
				{
					SceneCameraHandler::getInstance()->getSceneCamera()->setTopDownView();
					std::cout << "Projection mode: TOPDOWN VIEW\n";
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Render Modes"))
			{
				ImGui::SeparatorText("Render Modes"); // Render modes
				if (ImGui::MenuItem("Lit"))
				{	
					*rendermode = false;
					std::cout << "Render mode: Lit mode\n";
				}
				if (ImGui::MenuItem("Wireframe"))
				{
					*rendermode = true;
					std::cout << "Render mode: Wireframe mode\n";
				}
				ImGui::EndMenu();
			}
	ImGui::EndMainMenuBar();

	}
}

void Toolbar::spawnPhysicsCubes(int amt)
{

	GameObjectManager* manager = GameObjectManager::getInstance();
	AGameObject* object;
	for(int i = 0; i < amt; i++){
		manager->createObject(GameObjectManager::CUBE, nullptr, 0);
		object = manager->getSelectedObject();
		object->setName("Physics Cube");
		object->setPosition(0, 5, 0);
		new PhysicsComponent("PhysComp Cube", object);
	}

}
