#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include "resource.h"
#include "GraphicsClass.h"


//#define WIN32_LEAN_AND_MEAN

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize(HINSTANCE, int);
	void Shutdown();
	void Run();

	//LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);


private:
	bool Frame();
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	void ShutdownWindows();

private:
	//LPCWSTR		m_applicationName;
	HINSTANCE	g_hInst;
	HWND		g_hWnd;

	//InputClass*		m_Input;
	GraphicsClass*	m_Graphics;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

