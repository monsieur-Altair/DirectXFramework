#pragma once

#include <d3d11.h>
#include <xnamath.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class ShaderClass
{
private:
	struct ConstantBuffer
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightConstantBuffer
	{
		XMFLOAT4 vLightDir[2];
		XMFLOAT4 vLightColor[2];
		XMFLOAT4 vLightAmbient[2];
	};

public:
	ShaderClass();
	ShaderClass(const ShaderClass&);
	~ShaderClass();
	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(
		ID3D11DeviceContext*, 
		int, 
		XMMATRIX, 
		XMMATRIX, 
		XMMATRIX, 
		ID3D11ShaderResourceView*,
		XMFLOAT4,
		XMFLOAT4,
		XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*);
	HRESULT CompileShaderFromFile(WCHAR*, LPCSTR , LPCSTR , ID3DBlob**, HWND );
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	bool SetShaderParameters(
		ID3D11DeviceContext*, 
		XMMATRIX, 
		XMMATRIX, 
		XMMATRIX, 
		ID3D11ShaderResourceView*,
		XMFLOAT4,
		XMFLOAT4,
		XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* g_pVertexShader;
	ID3D11PixelShader*	g_pPixelShader;
	ID3D11InputLayout*	g_pVertexLayout;
	ID3D11Buffer*		g_pLightConstantBuffer;
	ID3D11Buffer*		g_pConstantBuffer;
	ID3D11SamplerState* g_pSampleState;
};


