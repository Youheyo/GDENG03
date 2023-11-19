#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "EngineTime.h"
#include "AGameObject.h"
#include "Cube.h"
#include "Plane.h"

class GameObjectManager{

public:
    typedef std::string String;
    typedef std::vector<AGameObject*> List;
    typedef std::unordered_map<String, AGameObject*> HashTable;

    enum PrimitiveType{
        NONE,
        CUBE,
        PLANE,
        SPHERE
    };

    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    AGameObject* findObjectByname(String name);
    List getAllObjects();
    int activeObjects();
    void updateAll();
    void renderAll(int viewportWidth, int viewportHeight, VertexShader* vs, PixelShader* ps);
    void addObject(AGameObject* gameObject);
    void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
    void deleteObject(AGameObject* gameObject);
    void deleteObjectByname(String name);
    void setSelectedObject(String name);
    void setSelectedObject(AGameObject* gameObject);
    AGameObject* getSelectedObject();

private:

    GameObjectManager();
    ~GameObjectManager();
    GameObjectManager(GameObjectManager const&) {};
    GameObjectManager& operator=(GameObjectManager const&) {};

    static GameObjectManager* sharedInstance;

    HashTable object_map;
    List object_list;
    AGameObject* selectedObject;

};