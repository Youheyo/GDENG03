#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::getInstance() {
    return sharedInstance;
}

void SceneCameraHandler::initialize() {
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy() {
    
}

void SceneCameraHandler::update() {
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix() {
    return sceneCamera->getViewMatrix();
}

Vector3D SceneCameraHandler::getSceneCameraPos()
{
    return this->sceneCamera->getPosition();
}

SceneCameraHandler::SceneCameraHandler() {
    this->sceneCamera= new Camera("SceneCamera");
}

SceneCameraHandler::~SceneCameraHandler() {
    
}

