#pragma once
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "Point.h"
#include <string>


class Camera : public GameObject, public InputListener{

public:
    Camera(std::string name);
    ~Camera();

    void draw(float width, float height, VertexShader *vs, PixelShader *ps) override;
    void update(float deltaTime) override;
    Matrix4x4 getViewMatrix();
    void updateViewMatrix();

    virtual void onKeyDown(int key) override;
    virtual void onKeyUp(int key) override;
    virtual void onMouseMove(const Point deltaPos) override;
    virtual void onLeftMouseDown(const Point deltaPos) override;
    virtual void onLeftMouseUp(const Point deltaPos) override;
    virtual void onRightMouseDown(const Point deltaPos) override;
    virtual void onRightMouseUp(const Point deltaPos) override;

private:
    float moveSpeed = 1.0f;


};