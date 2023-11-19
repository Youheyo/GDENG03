#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent{

public:
	PhysicsComponent(String name, AGameObject* owner);
	~PhysicsComponent();

	void perform(float deltaTime) override;
	void setGravity(bool gravity);

	RigidBody* getRigidBody();

private:
	float mass = 1000.0f;
	bool gravity;
	RigidBody* rigidBody;
};