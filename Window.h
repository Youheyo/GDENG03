#pragma once
#define NOMINMAX // ? Avoid conflict with Windows.h MIN and MAX declarations
#include <Windows.h>
#include "EngineTime.h"

class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();


	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};