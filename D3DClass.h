#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <xnamath.h>
#include <d3dx10math.h>

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();
	
	bool Initialize(HWND);
	void Shutdown();
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	//void GetProjectionMatrix(D3DXMATRIX&);
	//void GetWorldMatrix(D3DXMATRIX&);
	//void GetOrthoMatrix(D3DXMATRIX&);

	XMMATRIX GetProjectionMatrix();
	XMMATRIX GetWorldMatrix();
	XMMATRIX GetOrthoMatrix();

private:

	IDXGISwapChain*			g_pSwapChain;
	ID3D11Device*			g_pd3dDevice;
	ID3D11DeviceContext*	g_pImmediateContext;
	ID3D11RenderTargetView* g_pRenderTargetView;
	ID3D11Texture2D*		g_pDepthStencilBuffer;
	ID3D11DepthStencilView* g_pDepthStencilView;

	//ID3D11DepthStencilState*m_depthStencilState;
	//ID3D11RasterizerState*	m_rasterState;
	//D3DXMATRIX m_projectionMatrix;
	//D3DXMATRIX m_worldMatrix;
	//D3DXMATRIX m_orthoMatrix;

	XMMATRIX g_World;
	XMMATRIX g_Ortho;
	XMMATRIX g_Projection;
};

