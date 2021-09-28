#include "D3DClass.h"

D3DClass::D3DClass()
{
	g_pSwapChain = NULL;
	g_pd3dDevice = NULL;
	g_pImmediateContext = NULL;
	g_pRenderTargetView = NULL;
	g_pDepthStencilBuffer = NULL;
	g_pDepthStencilView = NULL;
	//m_depthStencilBuffer = 0;
	//m_depthStencilState = 0;
	//m_depthStencilView = 0;
	//m_rasterState = 0;
}


D3DClass::D3DClass(const D3DClass& other)
{
}


D3DClass::~D3DClass()
{
}

HRESULT D3DClass::Initialize(HWND g_hWnd)
{
	HRESULT							result;
	//IDXGIFactory*					factory;
	//IDXGIAdapter*					adapter;
	//IDXGIOutput*					adapterOutput;
	//DXGI_MODE_DESC*				displayModeList;
	//DXGI_ADAPTER_DESC				adapterDesc;
	//
	//DXGI_SWAP_CHAIN_DESC			swapChainDesc;
	DXGI_SWAP_CHAIN_DESC			swapChainDesc;
	D3D_DRIVER_TYPE					g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL				g_featureLevel = D3D_FEATURE_LEVEL_11_0;

	D3D11_TEXTURE2D_DESC			descDepth;
	
	//D3D11_DEPTH_STENCIL_DESC		depthStencilDesc;
	//D3D11_DEPTH_STENCIL_VIEW_DESC	depthStencilViewDesc;
	//ID3D11Texture2D*				g_pDepthStencilBuffer = NULL;
	//ID3D11DepthStencilView*		g_pDepthStencilView = NULL;
	//D3D11_RASTERIZER_DESC			rasterDesc;
	
	D3D11_VIEWPORT					viewport;
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;
	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = g_hWnd;
	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	//—Œ«ƒ¿Õ»≈ √À¿¬ÕŒ√Œ Œ¡⁄≈ “¿ » ÷≈œŒ◊ » Œ¡Ã≈Õ¿(ŒÕ¿  Œœ»–”≈“ — “¿–√≈“¿ Õ¿ Œ ÕŒ)
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		g_driverType = driverTypes[driverTypeIndex];
		result = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
		if (SUCCEEDED(result))
			break;
	}
	if (FAILED(result))
		return result;

	//ID3D11Texture2D* g_pDepthStencilBuffer = NULL;
	result = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_pDepthStencilBuffer);
	if (FAILED(result))
		return result;

	result = g_pd3dDevice->CreateRenderTargetView(g_pDepthStencilBuffer, NULL, &g_pRenderTargetView);
	g_pDepthStencilBuffer->Release();
	if (FAILED(result))
		return result;

	// ƒÀﬂ œ–¿¬»À‹ÕŒ√Œ Œ“Œ¡–¿∆≈Õ»ﬂ √≈ŒÃ≈“–»»
	// Create depth stencil texture
	// —Œ«ƒ¿Õ»≈ œŒ¬≈–’ÕŒ—“» ƒÀﬂ Z-¡”‘≈–¿ 
	//D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	result = g_pd3dDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencilBuffer);
	if (FAILED(result))
		return result;

	// Create the depth stencil view
	//—Œ«ƒ¿Õ»≈ Z - ¡”‘≈–¿
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	result = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencilBuffer, &descDSV, &g_pDepthStencilView);
	if (FAILED(result))
		return result;

	//” ¿«¿Õ»≈ ƒ»–≈ “”, ◊“Œ ›“Œ“ –≈Õƒ≈–-“¿–√≈“ »—œ. œŒ ”ÃŒÀ◊. » ¬ Õ≈√Œ ¬—≈ –»—Œ¬¿“‹
	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);


	// Setup the viewport
	//D3D11_VIEWPORT vp;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &viewport);

	return S_OK;

	//// Get the pointer to the back buffer.
	//hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
	//
	//// Create the render target view with the back buffer pointer.
	//hr = g_pd3dDevice->CreateRenderTargetView(backBufferPtr, NULL, &g_pRenderTargetView);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
	//
	//// Release pointer to the back buffer as we no longer need it.
	//backBufferPtr->Release();
	//backBufferPtr = 0;
	//
	//// Initialize the description of the depth buffer.
	//ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	//
	//// Set up the description of the depth buffer.
	//depthBufferDesc.Width = screenWidth;
	//depthBufferDesc.Height = screenHeight;
	//depthBufferDesc.MipLevels = 1;
	//depthBufferDesc.ArraySize = 1;
	//depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//depthBufferDesc.SampleDesc.Count = 1;
	//depthBufferDesc.SampleDesc.Quality = 0;
	//depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//depthBufferDesc.CPUAccessFlags = 0;
	//depthBufferDesc.MiscFlags = 0;
	//
	//// Create the texture for the depth buffer using the filled out description.
	//hr = g_pd3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &pBackBuffer);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
	//
	//// Initialize the description of the stencil state.
	//ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	//
	//// Set up the description of the stencil state.
	//depthStencilDesc.DepthEnable = true;
	//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//
	//depthStencilDesc.StencilEnable = true;
	//depthStencilDesc.StencilReadMask = 0xFF;
	//depthStencilDesc.StencilWriteMask = 0xFF;
	//
	//// Stencil operations if pixel is front-facing.
	//depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	//depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//
	//// Stencil operations if pixel is back-facing.
	//depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	//depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//
	//// Create the depth stencil state.
	//hr = g_pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
	//
	//// Set the depth stencil state.
	//g_pImmediateContext->OMSetDepthStencilState(m_depthStencilState, 1);
	//
	//// Initailze the depth stencil view.
	//ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	//
	//// Set up the depth stencil view description.
	//depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//depthStencilViewDesc.Texture2D.MipSlice = 0;
	//
	//// Create the depth stencil view.
	//hr = g_pd3dDevice->CreateDepthStencilView(pBackBuffer, &depthStencilViewDesc, &g_pDepthStecilView);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
	//
	//// Bind the render target view and depth stencil buffer to the output render pipeline.
	//g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStecilView);
	//
	//rasterDesc.AntialiasedLineEnable = false;
	//rasterDesc.CullMode = D3D11_CULL_BACK;
	//rasterDesc.DepthBias = 0;
	//rasterDesc.DepthBiasClamp = 0.0f;
	//rasterDesc.DepthClipEnable = true;
	//rasterDesc.FillMode = D3D11_FILL_SOLID;
	//rasterDesc.FrontCounterClockwise = false;
	//rasterDesc.MultisampleEnable = false;
	//rasterDesc.ScissorEnable = false;
	//rasterDesc.SlopeScaledDepthBias = 0.0f;
//
	//// Create the rasterizer state from the description we just filled out.
	//hr = g_pd3dDevice->CreateRasterizerState(&rasterDesc, &m_rasterState);
	//if (FAILED(hr))
	//{
	//	return false;
	//}
//
	//// Now set the rasterizer state.
	//g_pImmediateContext->RSSetState(m_rasterState);
//
	//// Setup the viewport for rendering.
	//viewport.Width = (float)screenWidth;
	//viewport.Height = (float)screenHeight;
	//viewport.MinDepth = 0.0f;
	//viewport.MaxDepth = 1.0f;
	//viewport.TopLeftX = 0.0f;
	//viewport.TopLeftY = 0.0f;
//
	//// Create the viewport.
	//g_pImmediateContext->RSSetViewports(1, &viewport);
//
	//// Setup the projection matrix.
	//fieldOfView = (float)D3DX_PI / 4.0f;
	//screenAspect = (float)screenWidth / (float)screenHeight;
	//
	//// Create the projection matrix for 3D rendering.
	//D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
//
	//// Initialize the world matrix to the identity matrix.
	//D3DXMatrixIdentity(&m_worldMatrix);
	// 
	//// Create an orthographic projection matrix for 2D rendering.
	//D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);
//
	//return true;
}

void D3DClass::Shutdown()
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	/*if (g_pSwapChain)
	{
		g_pSwapChain->SetFullscreenState(false, NULL);
	}

	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}*/

	if (g_pDepthStencilBuffer)
	{
		g_pDepthStencilBuffer->Release();
		g_pDepthStencilBuffer = 0;
	}

	if (g_pRenderTargetView)
	{
		g_pRenderTargetView->Release();
		g_pRenderTargetView = 0;
	}

	if (g_pImmediateContext)
	{
		g_pImmediateContext->Release();
		g_pImmediateContext->ClearState();
		g_pImmediateContext = 0;
	}

	if (g_pd3dDevice)
	{
		g_pd3dDevice->Release();
		g_pd3dDevice = 0;
	}

	if (g_pSwapChain)
	{
		g_pSwapChain->Release();
		g_pSwapChain = 0;
	}

	if (g_pDepthStencilView)
	{
		g_pDepthStencilView->Release();
		g_pDepthStencilView = 0;
	}

	return;
}

void D3DClass::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];
	// Setup the color to clear the buffer to.
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	// Clear the back buffer.
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, color);

	// Clear the depth buffer.
	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}


void D3DClass::EndScene()
{
	//// Present the back buffer to the screen since rendering is complete.
	//if (m_vsync_enabled)
	//{
	//	// Lock to screen refresh rate.
	//	g_pSwapChain->Present(1, 0);
	//}
	//else
	//{
	//	// Present as fast as possible.
	//	g_pSwapChain->Present(0, 0);
	//}

	g_pSwapChain->Present(0, 0);

	return;
}

ID3D11Device* D3DClass::GetDevice()
{
	return g_pd3dDevice;
}


ID3D11DeviceContext* D3DClass::GetDeviceContext()
{
	return g_pImmediateContext;
}

//void D3DClass::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
//{
//	projectionMatrix = m_projectionMatrix;
//	return;
//}
//
//
//void D3DClass::GetWorldMatrix(D3DXMATRIX& worldMatrix)
//{
//	worldMatrix = m_worldMatrix;
//	return;
//}
//
//
//void D3DClass::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
//{
//	orthoMatrix = m_orthoMatrix;
//	return;
//}
