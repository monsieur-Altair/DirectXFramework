#pragma once

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include <xnamath.h>
#include "CameraInform.h"

class DirectInputClass
{
private:
	IDirectInputDevice8* g_pKeyboard;
	IDirectInputDevice8* g_pMouse;

	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

	float rotx;
	float rotz;
	float scaleX;
	float scaleY;

	XMMATRIX Rotationx;
	XMMATRIX Rotationz;
public:
	DirectInputClass();
	DirectInputClass(DirectInputClass&);
	~DirectInputClass();

	bool Initialize(HINSTANCE, HWND);
	void Detect(double, HWND&, CameraInform&);
	void Shutdown();

};

