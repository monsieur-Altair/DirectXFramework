#include "DirectInputClass.h"

DirectInputClass::DirectInputClass()
{
	rotx = 0;
	rotz = 0;
	scaleX = 1.0f;
	scaleY = 1.0f;
	g_pKeyboard = NULL;
	g_pMouse = NULL;
}

DirectInputClass::DirectInputClass(DirectInputClass&)
{
}

DirectInputClass::~DirectInputClass()
{
}

void DirectInputClass::Shutdown()
{
	if (g_pKeyboard)
	{
		g_pKeyboard->Unacquire();
		g_pKeyboard->Release();
		g_pKeyboard = NULL;
	}
	if (g_pMouse)
	{
		g_pMouse->Unacquire();
		g_pMouse->Release();
		g_pMouse = NULL;
	}
	DirectInput->Release();
}

void DirectInputClass::Detect(double time, HWND& g_hWnd, CameraInform& camera)
{
	DIMOUSESTATE currMouseState;
	HRESULT result = S_OK;
	BYTE keyboardState[256];
	const float sensitive = 0.005f;


	result = g_pKeyboard->Acquire();
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not acquire keyboard", L"Error", MB_OK);
		return;
	}

	result = g_pMouse->Acquire();
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not acquire mouse", L"Error", MB_OK);
		return;
	}

	result = g_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &currMouseState);
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not get mouse state", L"Error", MB_OK);
		return;
	}

	result = g_pKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not get keyboard state", L"Error", MB_OK);
		return;
	}

	if (keyboardState[DIK_ESCAPE] & 0x80)
		PostMessage(g_hWnd, WM_DESTROY, 0, 0);

	float speed = 15.0f * time;

	if (keyboardState[DIK_A] & 0x80)
	{
		camera.moveLeftRight -= speed;
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		camera.moveLeftRight += speed;
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		camera.moveBackForward += speed;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		camera.moveBackForward -= speed;
	}
	if ((currMouseState.lX != mouseLastState.lX) || (currMouseState.lY != mouseLastState.lY))
	{
		camera.camYaw += currMouseState.lX * sensitive;

		camera.camPitch += currMouseState.lY * sensitive;

		mouseLastState = currMouseState;
	}

	return;
}




bool DirectInputClass::Initialize(HINSTANCE hInstance, HWND g_hWnd)
{
	HRESULT result = S_OK;
	result = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);
	if (FAILED(result))
		return false;

	result = DirectInput->CreateDevice(GUID_SysKeyboard, &g_pKeyboard, NULL);
	if (FAILED(result))
		return false;

	result = g_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		return false;

	//result = g_pKeyboard->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	result = g_pKeyboard->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	result = g_pKeyboard->Acquire();
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not initialize keyboard", L"Error", MB_OK);
		return false;
	}

	result = DirectInput->CreateDevice(GUID_SysMouse, &g_pMouse, NULL);
	if (FAILED(result))
		return false;


	result = g_pMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		return false;

	result = g_pMouse->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	//result = g_pMouse->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	result = g_pMouse->Acquire();
	if (FAILED(result))
	{
		MessageBox(g_hWnd, L"Could not initialize mouse", L"Error", MB_OK);
		return false;
	}

	return true;
}
