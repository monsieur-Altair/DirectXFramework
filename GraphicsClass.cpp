#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	this->m_D3D = 0;
	this->m_Camera = 0;
	this->m_Model = 0;
	this->m_Shader = 0;
	this->m_UI = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HWND g_hWnd)
{
	bool result;
	WCHAR* textureFilename = L"texture.png";

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(g_hWnd);
	if (!result)
	{
		MessageBox(g_hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}
	
	// Set the initial position of the camera.
	m_Camera->SetEye(XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f));
	
	
	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	
	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), textureFilename);
	if (!result)
	{
		MessageBox(g_hWnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the color shader object.
	m_Shader = new ShaderClass;
	if (!m_Shader)
	{
		return false;
	}
	
	// Initialize the color shader object.
	result = m_Shader->Initialize(m_D3D->GetDevice(), g_hWnd);
	if (!result)
	{
		MessageBox(g_hWnd, L"Could not initialize the shader object.", L"Error", MB_OK);
		return false;
	}


	m_UI = new UIClass;
	if (!m_UI)
	{
		return false;
	}
	
	result = m_UI->Intialize(m_D3D->GetSwapChain());
	if (!result)
	{
		MessageBox(g_hWnd, L"Could not initialize the UI object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_Shader)
	{
		m_Shader->Shutdown();
		delete m_Shader;
		m_Shader = 0;
	}
		
	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_UI)
	{
		m_UI->Shutdown();
		delete m_UI;
		m_UI = 0;
	}

	return;
}


bool GraphicsClass::Frame(CameraInform& cameraInf)
{
	bool result;

	// Render the graphics scene.
	result = this->Render(cameraInf);
	if (!result)
	{
		return false;
	}
	return true;
}


bool GraphicsClass::Render(CameraInform& cameraInf)
{
	//D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	XMMATRIX viewMatrix, projectionMatrix, worldMatrix;

	bool result;

	//float r = 0.23f,
	//	g = 0.05f,
	//	b = 0.36f,
	//	a = 1.0f;

	float r = 0.03f,
		g = 0.05f,
		b = 0.06f,
		a = 1.0f;




	D3D_DRIVER_TYPE g_driverType = this->m_D3D->GetDriverType();
	static float t = 0.0f;
	if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
	{
		t += (float)XM_PI * 0.0125f;
	}
	else
	{
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;
	}


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(r, g, b, a);

	//Generate the view matrix based on the camera's position.
	m_Camera->Render(cameraInf);
	//m_Camera->Render();

	m_D3D->SetWorldMatrix(t);
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	viewMatrix = m_Camera->GetViewMatrix();
	worldMatrix = m_D3D->GetWorldMatrix();
	projectionMatrix = m_D3D->GetProjectionMatrix();
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());


	
	// Render the model using the color shader.
	result = m_Shader->Render(
		m_D3D->GetDeviceContext(),
		m_Model->GetIndexCount(),
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		m_Model->GetTexture()
	);

	if (!result)
	{
		return false;
	}

	m_UI->Draw();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	return true;
}

