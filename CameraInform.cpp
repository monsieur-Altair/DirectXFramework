#pragma once
#include "CameraInform.h"

CameraInform::CameraInform()
{
	moveLeftRight = 0.0f;
	moveBackForward = 0.0;
	camYaw = 0.0;
	camPitch = 0.0;
}

CameraInform::CameraInform(const CameraInform& obj)
{
	this->moveLeftRight = obj.moveLeftRight;
	this->moveBackForward = obj.moveBackForward;
	this->camYaw = obj.camYaw;
	this->camPitch = obj.camPitch;
}

CameraInform::~CameraInform()
{

}