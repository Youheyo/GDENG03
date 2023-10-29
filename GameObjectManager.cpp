#include "GameObjectManager.h"


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
		Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
		object = cube;
		break;
	case PLANE:
		std::cout << "Plane Initialized" << std::endl;
		break;
	case SPHERE:
		std::cout << "Sphere Initialized" << std::endl;
		break;

	default:
		break;
	}

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

void GameObjectManager::setSelectedObject(GameObject* gameObject) {
	sharedInstance->selectedObject = gameObject;
}

GameObject* GameObjectManager::getSelectedObject() {
	return sharedInstance->selectedObject;
}


GameObjectManager::~GameObjectManager() {
    
}