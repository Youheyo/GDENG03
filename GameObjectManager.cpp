#include "GameObjectManager.h"
GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	return sharedInstance;
}

void GameObjectManager::initialize() {
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy() {
	delete sharedInstance;
}

GameObject* GameObjectManager::findObjectByname(String name) {
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		if(sharedInstance->object_list[i]->getName() == name){
			return sharedInstance->object_list[i];
		}
	}
}

std::vector<GameObject*> GameObjectManager::getAllObjects() {
	return sharedInstance->object_list;
}

int GameObjectManager::activeObjects() {
	return sharedInstance->object_list.size();
}

void GameObjectManager::updateAll() {
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		sharedInstance->object_list[i]->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vs, PixelShader* ps) {
		
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		sharedInstance->object_list[i]->draw(viewportWidth, viewportHeight, vs, ps);
	}
	
}

void GameObjectManager::addObject(GameObject* gameObject) {
	sharedInstance->object_list.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader) {
	
	GameObject* object = nullptr;
	
	switch (type)
	{
		case CUBE:
			std::cout << "Cube Initialized" << std::endl;
			object = new Cube("Cube", shaderByteCode, sizeShader);
			break;
		case PLANE:
			std::cout << "Plane Initialized" << std::endl;
			object = new Cube("Plane", shaderByteCode, sizeShader);
			object->setScale(1,0,1);
			break;
		case SPHERE:
			std::cout << "Sphere Initialized" << std::endl;
			break;

		default:
			object = nullptr;
			break;
	}

	if(object == nullptr){
		std::cout << "\x1B[31mNo object has been created. Object is either unsupported or unimplemented!\x1B[0m" << std::endl;
		return;
	}

	sharedInstance->addObject(object);
	setSelectedObject(object);

}

void GameObjectManager::deleteObject(GameObject* gameObject) {
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		if(sharedInstance->object_list[i] == gameObject){
			//Remove the object
			break;
		}
	}
}

void GameObjectManager::deleteObjectByname(String name) {
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		if(sharedInstance->object_list[i]->getName() == name){
			//Remove the object
			break;
		}
	}
}

void GameObjectManager::setSelectedObject(String name)
{
	for(int i = 0 ; i < sharedInstance->object_list.size(); i++){
		if(sharedInstance->object_list[i]->getName() == name){
			sharedInstance->selectedObject = sharedInstance->object_list[i];
			break;
		}
	}
}

void GameObjectManager::setSelectedObject(GameObject* gameObject) {
	sharedInstance->selectedObject = gameObject;
}

GameObject* GameObjectManager::getSelectedObject() {
	return sharedInstance->selectedObject;
}

GameObjectManager::GameObjectManager(){
	
}

GameObjectManager::~GameObjectManager() {
    
}