#pragma once

#include <d3dx10math.h>
#include <xnamath.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetEye(XMVECTOR&);
	void SetAt(XMVECTOR&); 
	void SetUp (XMVECTOR&);

	//D3DXVECTOR3 GetPosition();
	//D3DXVECTOR3 GetRotation();
	XMVECTOR GetEye();
	XMVECTOR GetAt();
	XMVECTOR GetUp();


	void Render();
	//void GetViewMatrix(D3DXMATRIX&);
	XMMATRIX GetViewMatrix();

private:
	//float m_positionX, m_positionY, m_positionZ;
	//float m_rotationX, m_rotationY, m_rotationZ;
	//D3DXMATRIX m_viewMatrix;
	XMVECTOR eye, at, up;
	XMMATRIX g_View;
};

