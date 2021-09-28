#include "SystemClass.h"

SystemClass::SystemClass()
{
	this->g_hInst = NULL;
	this->g_hWnd = NULL;
	this->m_Graphics = NULL;
}

SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	//int screenWidth, screenHeight;
	HRESULT result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	//screenWidth = 0;
	//screenHeight = 0;

	// Initialize the windows api.
	this->InitWindow(hInstance, nCmdShow);

	//// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	//m_Input = new InputClass;
	//if (!m_Input)
	//{
	//	return false;
	//}
	//
	//// Initialize the input object.
	//m_Input->Initialize();
	//
	
	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}
	
	// Initialize the graphics object.
	result = m_Graphics->Initialize(this->g_hWnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	// Release the graphics object.
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = NULL;
	}
	this->g_hWnd = NULL;
	this->g_hInst = NULL;

	//// Release the input object.
	//if (m_Input)
	//{
	//	delete m_Input;
	//	m_Input = 0;
	//}
	//
	// Shutdown the window.
	//ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	bool done, result;


	// Initialize the message structure.
	
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
			// Otherwise do the frame processing.
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}

	}
	return;
}

bool SystemClass::Frame()
{
	bool result;


	//// Check if the user pressed escape and wants to exit the application.
	//if (m_Input->IsKeyDown(VK_ESCAPE))
	//{
	//	return false;
	//}

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

//LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
//{
//	switch (umsg)
//	{
//		// Check if a key has been pressed on the keyboard.
//		case WM_KEYDOWN:
//		{
//			// If a key is pressed send it to the input object so it can record that state.
//			m_Input->KeyDown((unsigned int)wparam);
//			return 0;
//		}
//
//		// Check if a key has been released on the keyboard.
//		case WM_KEYUP:
//		{
//			// If a key is released then send it to the input object so it can unset the state for that key.
//			m_Input->KeyUp((unsigned int)wparam);
//			return 0;
//		}
//
//		// Any other messages send to the default message handler as our application won't make use of them.
//		default:
//		{
//			return DefWindowProc(hwnd, umsg, wparam, lparam);
//		}
//	}
//}

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
	RECT rc = { 0, 0, 1500, 750 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	this->g_hWnd = CreateWindow(L"TutorialWindowClass", L"Ìåëüíèêîâ Ìàêñèì 924401", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!this->g_hWnd)
		return E_FAIL;

	ShowWindow(this->g_hWnd, nCmdShow);

	return S_OK;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	//ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	//if (FULL_SCREEN)
	//{
	//	ChangeDisplaySettings(NULL, 0);
	//}
	//
	// Remove the window.
	//DestroyWindow(this->g_hWnd);
	//this->g_hWnd = NULL;

	//
	// Remove the application instance.
	//UnregisterClass(m_applicationName, m_hinstance);
	//m_hinstance = NULL;
	//
	// Release the pointer to this class.
	//ApplicationHandle = NULL;

	return;
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