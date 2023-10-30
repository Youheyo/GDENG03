#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "EngineTime.h"
#include "GameObject.h"
#include "Cube.h"

class GameObjectManager{

public:
    typedef std::string String;
    typedef std::vector<GameObject*> List;
    typedef std::unordered_map<String, GameObject*> HashTable;

    enum PrimitiveType{
        NONE,
        CUBE,
        PLANE,
        SPHERE
    };

    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    GameObject* findObjectByname(String name);
    List getAllObjects();
    int activeObjects();
    void updateAll();
    void renderAll(int viewportWidth, int viewportHeight, VertexShader* vs, PixelShader* ps);
    void addObject(GameObject* gameObject);
    void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
    void deleteObject(GameObject* gameObject);
    void deleteObjectByname(String name);
    void setSelectedObject(String name);
    void setSelectedObject(GameObject* gameObject);
    GameObject* getSelectedObject();

private:

    GameObjectManager();
    ~GameObjectManager();
    GameObjectManager(GameObjectManager const&) {};
    GameObjectManager& operator=(GameObjectManager const&) {};

    static GameObjectManager* sharedInstance;

    List object_list;
    GameObject* selectedObject;

};