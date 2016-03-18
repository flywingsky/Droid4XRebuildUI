#pragma once
#ifdef D4XSHIP_EXPORTS
#define D4XSHIP_API __declspec(dllexport)
#else
#define D4XSHIP_API __declspec(dllimport)
#endif
#include <string>
#include <thread>
#include "shipdef.h"

class Ship
{
public:
	virtual bool init(const std::wstring& name, void* hwnd, int wnd_width, int wnd_height) = 0;
	virtual void start(const StartProcCallback& = nullptr) = 0;
	virtual void mouse_event(mouse_event_type type, int x, int y) = 0;
	virtual void move_event(int x, int y) = 0;
	virtual void size_event(int w, int h) = 0;
	virtual void show_vkey_setting() = 0;
};

extern "C" D4XSHIP_API Ship* createShip();
