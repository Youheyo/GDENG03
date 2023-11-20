#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner){
    
	// * When new physics component is initialized. Register to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// * Create Rigid Body in world

	Vector3D scale = this->getOwner()->getScale();
	Transform transform; transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.getX() / 2, scale.getY() / 2 ,scale.getZ() / 2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);
	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent() {
    BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime) {
    const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	
	this->getOwner()->recomputeMatrix(matrix);
}

void PhysicsComponent::setGravity(bool gravity)
{
	this->rigidBody->enableGravity(gravity);
}

RigidBody* PhysicsComponent::getRigidBody() {
    return this->rigidBody;
}
