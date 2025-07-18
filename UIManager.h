#pragma once
#include "GraphicsEngine.h"
#include "UINames.h"
#include "AUIScreen.h"
#include <vector>
#include <unordered_map>

class AUIScreen;

class UIManager {

public:

    typedef std::string String;
    typedef std::vector<AUIScreen*> UIList;
    typedef std::unordered_map<String, AUIScreen*> UITable;

    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawAllUI();

    static const int WINDOW_WIDTH = 1440;
    static const int WINDOW_HEIGHT = 900;

private:

    UIManager(HWND windowHandle);
    ~UIManager();
    UIManager(UIManager const&) {};
    UIManager& operator=(UIManager const&) {};

    static UIManager* sharedInstance;

    UIList uiList;
    UITable uiTable;

    friend class AUIScreen;
};