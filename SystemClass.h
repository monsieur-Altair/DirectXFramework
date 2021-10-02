#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "resource.h"
#include "GraphicsClass.h"
#include "Constants.h"
#include "DirectInputClass.h"
#include "TimerClass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize(HINSTANCE, int);
	void Shutdown();
	void Run();

private:
	bool Frame(double);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

	HINSTANCE	g_hInst;
	HWND		g_hWnd;

	DirectInputClass* m_Input;
	GraphicsClass*	  m_Graphics;
	TimerClass*		  m_Timer;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

