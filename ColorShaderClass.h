#pragma once

#include <d3d11.h>
#include <xnamath.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

class ColorShaderClass
{
private:
	struct ConstantBuffer
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();
	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*);
	HRESULT CompileShaderFromFile(WCHAR*, LPCSTR , LPCSTR , ID3DBlob**, HWND );
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* g_pVertexShader;
	ID3D11PixelShader* g_pPixelShader;
	ID3D11InputLayout* g_pVertexLayout;
	ID3D11Buffer* g_pConstantBuffer;
};


//#pragma once
//
//#include <d3d11.h>
//#include <d3dx10math.h>
//#include <d3dx11async.h>
//#include <fstream>
//using namespace std;
//
//class ColorShaderClass
//{
//private:
//	struct MatrixBufferType
//	{
//		D3DXMATRIX world;
//		D3DXMATRIX view;
//		D3DXMATRIX projection;
//	};
//
//public:
//	ColorShaderClass();
//	ColorShaderClass(const ColorShaderClass&);
//	~ColorShaderClass();
//	bool Initialize(ID3D11Device*, HWND);
//	void Shutdown();
//	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
//
//private:
//	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
//	void ShutdownShader();
//	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
//
//	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
//	void RenderShader(ID3D11DeviceContext*, int);
//
//private:
//	ID3D11VertexShader* m_vertexShader;
//	ID3D11PixelShader* m_pixelShader;
//	ID3D11InputLayout* m_layout;
//	ID3D11Buffer* m_matrixBuffer;
//};

