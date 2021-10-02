#pragma once

struct CameraInform 
{
	float moveLeftRight;
	float moveBackForward;

	float camYaw;
	float camPitch;

	CameraInform();
	CameraInform(const CameraInform&);
	~CameraInform();
};