#pragma once

#include <d3dx10math.h>
#include <xnamath.h>
#include "CameraInform.h"

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetEye(XMVECTOR&);
	void SetAt(XMVECTOR&); 
	void SetUp (XMVECTOR&);

	XMVECTOR& GetEye();
	XMVECTOR& GetAt();
	XMVECTOR& GetUp();

	void Render(CameraInform&);
	void Render();
	XMMATRIX& GetViewMatrix();

private:

	XMVECTOR eye, at, up;
	XMMATRIX g_View;
	XMVECTOR DefaultForward, DefaultRight, camForward, camRight;
	XMMATRIX camRotationMatrix;
};

