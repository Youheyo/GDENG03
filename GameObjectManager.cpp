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

AGameObject* GameObjectManager::findObjectByname(String name) {
	for(int i = 0; i < sharedInstance->object_list.size(); i++){
		if(sharedInstance->object_list[i]->getName() == name){
			return sharedInstance->object_list[i];
		}
	}
}

std::vector<AGameObject*> GameObjectManager::getAllObjects() {
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

void GameObjectManager::addObject(AGameObject* gameObject) {

	if(sharedInstance->object_map[gameObject->getName()] != NULL){
		int count = 1;
		String string = gameObject->getName() + std::to_string(count);
		while (sharedInstance->object_map[string] != NULL)
		{
			count++;
			string = gameObject->getName() + std::to_string(count);
		}
		
		gameObject->setName(string);
		sharedInstance->object_map[string] = gameObject;
	}
	else{
		sharedInstance->object_map[gameObject->getName()] = gameObject;
	}
	sharedInstance->object_list.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader) {
	
	AGameObject* object = nullptr;
	
	switch (type)
	{
		case CUBE:
			std::cout << "Cube Initialized" << std::endl;
			object = new Cube("Cube", shaderByteCode, sizeShader);
			break;
		case PLANE:
			std::cout << "Plane Initialized" << std::endl;
			object = new Plane("Plane", shaderByteCode, sizeShader);
			// object->setScale(1,0,1);
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

void GameObjectManager::deleteObject(AGameObject* gameObject) {

	sharedInstance->object_map.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < sharedInstance->object_list.size(); i++) {
		if (sharedInstance->object_list[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		sharedInstance->object_list.erase(sharedInstance->object_list.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::deleteObjectByname(String name) {
		AGameObject* object = sharedInstance->findObjectByname(name);

	if (object != NULL) {
		sharedInstance->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(String name)
{
	if(sharedInstance->object_map[name] != NULL){
		sharedInstance->setSelectedObject(sharedInstance->object_map[name]);
	}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject) {
	sharedInstance->selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject() {
	return sharedInstance->selectedObject;
}

GameObjectManager::GameObjectManager(){
	
}

GameObjectManager::~GameObjectManager() {
    
}