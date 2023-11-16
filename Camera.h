#pragma once
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "AGameObject.h"
#include "Point.h"
#include <string>

class Camera : public AGameObject, public InputListener
{
public:
    Camera(std::string name);
    ~Camera();

    void draw(float width, float height, VertexShader* vs, PixelShader* ps) override;
    void update(float deltaTime) override;
    Matrix4x4 getViewMatrix();

    virtual void onKeyDown(int key) override;
    virtual void onKeyUp(int key) override;
    virtual void onMouseMove(const Point deltaPos) override;
    virtual void onLeftMouseDown(const Point deltaPos) override;
    virtual void onLeftMouseUp(const Point deltaPos) override;
    virtual void onRightMouseDown(const Point deltaPos) override;
    virtual void onRightMouseUp(const Point deltaPos) override;


    void savePerspectiveView();
    void setPerspectiveView();
    void setTopDownView();

private:
    void updateViewMatrix();

    float ticks = 0.0f;
    float mouseDown = false;

    Vector3D forwardDirection;
    Vector3D backwardDirection;
    Matrix4x4 viewMatrix;
    //float forwardDirection = 0.0f;
    //Matrix4x4 worldCameraMatrix;

    bool canMouseMove = true;
    Vector3D perspectivePos;
    Vector3D perspectiveRot;
};