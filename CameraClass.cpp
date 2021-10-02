#include "CameraClass.h"

CameraClass::CameraClass()
{
	this->eye = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);
	this->at =  XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	this->up =  XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	this->DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	this->DefaultRight =   XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	this->camForward =	   XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	this->camRight =	   XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
	this->camRotationMatrix = other.camRotationMatrix;
	this->DefaultForward = other.DefaultForward;
	this->DefaultRight = other.DefaultRight;
	this->camForward = other.camForward;
	this->camRight = other.camRight;
	this->g_View = other.g_View;
	this->eye = other.eye;
	this->at = other.at;
	this->up = other.up;
}


CameraClass::~CameraClass()
{
}

void CameraClass::SetEye(XMVECTOR& vect)
{
	
	this->eye = vect;
}

void CameraClass::SetAt(XMVECTOR& vect)
{
	this->at = vect;
}

void CameraClass::SetUp(XMVECTOR& vect)
{
	this->up = vect;
}

XMVECTOR& CameraClass::GetEye()
{
	return this->eye;
}

XMVECTOR& CameraClass::GetAt()
{
	return at;
}

XMVECTOR& CameraClass::GetUp()
{
	return up;
}

void CameraClass::Render(CameraInform& cameraInf)
{
	//Yaw is the rotation left/right (y-axis), pitch is the rotation up/down (x-axis) 
	//and Roll is the rotation like your doing a cartwheel (z-axis).
	camRotationMatrix = XMMatrixRotationRollPitchYaw(cameraInf.camPitch, cameraInf.camYaw, 0);
	at = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	at = XMVector3Normalize(at);

	camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	up = XMVector3Cross(camForward, camRight);

	eye += cameraInf.moveLeftRight * camRight;
	eye += cameraInf.moveBackForward * camForward;

	cameraInf.moveLeftRight = 0.0f;
	cameraInf.moveBackForward = 0.0f;

	at = eye + at;

	g_View = XMMatrixLookAtLH(eye, at, up);
}

void CameraClass::Render()
{
	g_View = XMMatrixLookAtLH(eye, at, up);
}

XMMATRIX& CameraClass::GetViewMatrix()
{
	return g_View;
}