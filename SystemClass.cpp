#include "SystemClass.h"
#include <iostream>
#include <fstream>


SystemClass::SystemClass()
{
	this->g_hInst = NULL;
	this->g_hWnd = NULL;
	this->m_Graphics = NULL;
	this->m_Input = NULL;
	this->m_Timer = NULL;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	bool result;

	// Initialize the windows api.
	this->InitWindow(hInstance, nCmdShow);

	m_Timer = new TimerClass;
	if (!m_Timer)
		return false;

	m_Input = new DirectInputClass;
	if (!m_Input)
		return false;

	result = m_Input->Initialize(hInstance,g_hWnd);
	if (!result)
		return false;

	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
		return false;

	result = m_Graphics->Initialize(this->g_hWnd);
	if (!result)
		return false;

	return true;
}

void SystemClass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = NULL;
	}
	this->g_hWnd = NULL;
	this->g_hInst = NULL;

	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = NULL;
	}

	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = NULL;
	}

	return;
}

void SystemClass::Run()
{
	bool done, result;
	
	double frameTime = 0.0f;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Main message loop
	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			m_Timer->CountFrames();
			frameTime = m_Timer->GetFrameTime();

			// Otherwise do the frame processing.
			result = Frame(frameTime);
			if (!result)
			{
				done = true;
			}
		}

	}
	return;
}

bool SystemClass::Frame(double time)
{
	bool result;
	static CameraInform camInform;

	m_Input->Detect(time, g_hWnd, camInform);

	result = m_Graphics->Frame(camInform);
	if (!result)
	{
		return false;
	}

	return true;
}

HRESULT SystemClass::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ÐÅÃÈÑÒÐÀÖÈß ÊËÀÑÑÀ ÎÊÍÀ
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;



	// ÑÎÇÄÀÍÈÅ ÎÊÍÀ 
	this->g_hInst= hInstance;
	RECT rc = { 0, 0, LENGTH_WINDOW , WIDTH_WINDOW };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	this->g_hWnd = CreateWindow(L"TutorialWindowClass", L"Ìåëüíèêîâ Ìàêñèì 924401", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!this->g_hWnd)
		return E_FAIL;

	ShowWindow(this->g_hWnd, nCmdShow);
	//UpdateWindow(g_hWnd);

	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}