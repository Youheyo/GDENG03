#include "AUIScreen.h"

AUIScreen::AUIScreen(std::string name)
{
    this->name = name;
    UIManager::getInstance()->uiList.push_back(this);
}

AUIScreen::~AUIScreen()
{
}

std::string AUIScreen::getName()
{
    return this->name;
}
