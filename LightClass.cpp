#include "LightClass.h"

LightClass::LightClass()
{
	this->ambient = XMFLOAT4(0, 0, 0, 0);
	this->diffuseColor = XMFLOAT4(0, 0, 0, 0);
	this->direction = XMFLOAT4(0, 0, 0,0);
}

LightClass::LightClass(const LightClass& obj)
{
	this->ambient = obj.ambient;
	this->diffuseColor = obj.diffuseColor;
	this->direction = obj.direction;
}

LightClass::~LightClass()
{
}

void LightClass::SetDiffuseColor(float r, float g, float b, float a)
{
	this->diffuseColor = XMFLOAT4(r, g, b, a);
}

void LightClass::SetAmbient(float r, float g, float b, float a)
{
	this->ambient = XMFLOAT4(r, g, b, a);

}

void LightClass::SetDirection(float x, float y, float z)
{
	this->direction = XMFLOAT4(x, y, z, 1);
}

XMFLOAT4& LightClass::GetDiffuseColor()
{
	return diffuseColor;
}

XMFLOAT4& LightClass::GetAmbient()
{
	return ambient;
}

XMFLOAT4& LightClass::GetDirection()
{
	return direction;
}
