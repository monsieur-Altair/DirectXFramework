#include "TextureClass.h"

TextureClass::TextureClass()
{
	g_pTexture = NULL;
}

TextureClass::TextureClass(const TextureClass& obj)
{
	this->g_pTexture = obj.g_pTexture;
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(
		device,
		filename,
		NULL,
		NULL,
		&g_pTexture,
		NULL);
	if (FAILED(result))
		return false;
	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture resource.
	if (g_pTexture)
	{
		g_pTexture->Release();
		g_pTexture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return g_pTexture;
}