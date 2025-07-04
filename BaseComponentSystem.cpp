#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = NULL;


BaseComponentSystem* BaseComponentSystem::getInstance() {
    return sharedInstance;
}

void BaseComponentSystem::initialize() {
    sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy() {
    delete sharedInstance;
}

PhysicsSystem* BaseComponentSystem::BaseComponentSystem::getPhysicsSystem() {
    return sharedInstance->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem() {
    physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem() {
    
}

