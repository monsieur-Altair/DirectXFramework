#pragma once

#include <d3d11.h>
#include <xnamath.h>

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetAmbient(float, float, float, float);
	void SetDirection(float, float, float);

	XMFLOAT4& GetDiffuseColor();
	XMFLOAT4& GetAmbient();
	XMFLOAT4& GetDirection();

private:
	XMFLOAT4 direction;
	XMFLOAT4 diffuseColor;
	XMFLOAT4 ambient;
};

