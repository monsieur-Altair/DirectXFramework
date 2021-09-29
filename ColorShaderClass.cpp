#include "ColorShaderClass.h"

ColorShaderClass::ColorShaderClass()
{
	g_pVertexShader = 0;
	g_pPixelShader = 0;
	g_pVertexLayout = 0;
	g_pConstantBuffer = 0;
}


ColorShaderClass::ColorShaderClass(const ColorShaderClass& other)
{
}


ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"Tutorial05.fx");
	if (!result)
	{
		return false;
	}

	return true;
}

void ColorShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

bool ColorShaderClass::Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	bool result;


	// Set the shader parameters that it will use for rendering.
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader.
	RenderShader(deviceContext, indexCount);

	return true;
}

//bool ColorShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
//{
//	HRESULT result;
//	ID3D10Blob* errorMessage;
//	ID3D10Blob* vertexShaderBuffer;
//	ID3D10Blob* pixelShaderBuffer;
//	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
//	unsigned int numElements;
//	D3D11_BUFFER_DESC matrixBufferDesc;
//
//
//	// Initialize the pointers this function will use to null.
//	errorMessage = 0;
//	vertexShaderBuffer = 0;
//	pixelShaderBuffer = 0;
//
//	// Compile the vertex shader code.
//	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
//		&vertexShaderBuffer, &errorMessage, NULL);
//	if (FAILED(result))
//	{
//		// If the shader failed to compile it should have writen something to the error message.
//		if (errorMessage)
//		{
//			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
//		}
//		// If there was nothing in the error message then it simply could not find the shader file itself.
//		else
//		{
//			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
//		}
//
//		return false;
//	}
//
//	// Compile the pixel shader code.
//	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
//		&pixelShaderBuffer, &errorMessage, NULL);
//	if (FAILED(result))
//	{
//		// If the shader failed to compile it should have writen something to the error message.
//		if (errorMessage)
//		{
//			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
//		}
//		// If there was  nothing in the error message then it simply could not find the file itself.
//		else
//		{
//			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
//		}
//
//		return false;
//	}
//
//
//	// Create the vertex shader from the buffer.
//	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &g_pVertexShader);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Create the pixel shader from the buffer.
//	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &g_pPixelShader);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Now setup the layout of the data that goes into the shader.
//	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
//	polygonLayout[0].SemanticName = "POSITION";
//	polygonLayout[0].SemanticIndex = 0;
//	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
//	polygonLayout[0].InputSlot = 0;
//	polygonLayout[0].AlignedByteOffset = 0;
//	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	polygonLayout[0].InstanceDataStepRate = 0;
//
//	polygonLayout[1].SemanticName = "COLOR";
//	polygonLayout[1].SemanticIndex = 0;
//	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//	polygonLayout[1].InputSlot = 0;
//	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
//	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
//	polygonLayout[1].InstanceDataStepRate = 0;
//
//	// Get a count of the elements in the layout.
//	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
//
//	// Create the vertex input layout.
//	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
//		vertexShaderBuffer->GetBufferSize(), &g_pVertexLayout);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
//	vertexShaderBuffer->Release();
//	vertexShaderBuffer = 0;
//
//	pixelShaderBuffer->Release();
//	pixelShaderBuffer = 0;
//
//	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
//	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//	matrixBufferDesc.ByteWidth = sizeof(ConstantBuffer);
//	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//	matrixBufferDesc.MiscFlags = 0;
//	matrixBufferDesc.StructureByteStride = 0;
//
//	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
//	result = device->CreateBuffer(&matrixBufferDesc, NULL, &g_pConstantBuffer);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	return true;
//}

bool ColorShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* filename)
{
	HRESULT result;
	//ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	unsigned int numElements;
	D3D11_BUFFER_DESC constBufferDesc;


	// Initialize the pointers this function will use to null.
	//errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code.
	result = CompileShaderFromFile(L"Tutorial05.fx", "VS", "vs_4_0", &vertexShaderBuffer, hwnd);
	if (FAILED(result))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return false;
	}

	// Compile the pixel shader code.
	result = CompileShaderFromFile(L"Tutorial05.fx", "PS", "ps_4_0", &pixelShaderBuffer, hwnd);
	if (FAILED(result))
	{
		MessageBox(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return false;
	}


	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &g_pVertexShader);
	if (FAILED(result))
	{
		vertexShaderBuffer->Release();
		return false;
	}

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &g_pPixelShader);
	if (FAILED(result))
	{
		pixelShaderBuffer->Release();
		return false;
	}

	// Now setup the layout of the data that goes into the shader.
	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	/*polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;*/

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2]=
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// Get a count of the elements in the layout.
	numElements = ARRAYSIZE(polygonLayout);

	// Create the vertex input layout.
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &g_pVertexLayout);
	
	if (FAILED(result))
	{
		return false;
	}




	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	if (vertexShaderBuffer) 
	{
		vertexShaderBuffer->Release();
		vertexShaderBuffer = 0;
	}

	if (pixelShaderBuffer)
	{
		pixelShaderBuffer->Release();
		pixelShaderBuffer = 0;
	}


	ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constBufferDesc.CPUAccessFlags = 0;
	//constBufferDesc.MiscFlags = 0;
	//constBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&constBufferDesc, NULL, &g_pConstantBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ColorShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	if (errorMessage)
	{
		errorMessage->Release();
		errorMessage = 0;
	}

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}


HRESULT ColorShaderClass::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut, HWND hwnd)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputShaderErrorMessage(pErrorBlob, hwnd, szFileName);
		else
			MessageBox(hwnd, szFileName, L"Missing Shader File", MB_OK);
		
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}



void ColorShaderClass::ShutdownShader()
{
	// Release the matrix constant buffer.
	if (g_pConstantBuffer)
	{
		g_pConstantBuffer->Release();
		g_pConstantBuffer = 0;
	}

	// Release the layout.
	if (g_pVertexLayout)
	{
		g_pVertexLayout->Release();
		g_pVertexLayout = 0;
	}

	// Release the pixel shader.
	if (g_pPixelShader)
	{
		g_pPixelShader->Release();
		g_pPixelShader = 0;
	}

	// Release the vertex shader.
	if (g_pVertexShader)
	{
		g_pVertexShader->Release();
		g_pVertexShader = 0;
	}

	return;
}



/////////////////////////
//bool ColorShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
//	XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
//{
//	HRESULT result;
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	ConstantBuffer* dataPtr;
//	unsigned int bufferNumber;
//
//	// Transpose the matrices to prepare them for the shader.
//	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
//	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
//	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);
//
//	// Lock the constant buffer so it can be written to.
//	result = deviceContext->Map(g_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
//	if (FAILED(result))
//	{
//		return false;
//	}
//
//	// Get a pointer to the data in the constant buffer.
//	dataPtr = (ConstantBuffer*)mappedResource.pData;
//
//	// Copy the matrices into the constant buffer.
//	dataPtr->world = worldMatrix;
//	dataPtr->view = viewMatrix;
//	dataPtr->projection = projectionMatrix;
//
//	// Unlock the constant buffer.
//	deviceContext->Unmap(g_pConstantBuffer, 0);
//
//	// Set the position of the constant buffer in the vertex shader.
//	bufferNumber = 0;
//
//	// Finanly set the constant buffer in the vertex shader with the updated values.
//	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &g_pConstantBuffer);
//
//	return true;
//}

///////////////////////
bool ColorShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	HRESULT result;
	ConstantBuffer dataPtr;
	unsigned int bufferNumber;


	// Copy the matrices into the constant buffer.
	dataPtr.world = XMMatrixTranspose(worldMatrix);
	dataPtr.view = XMMatrixTranspose(viewMatrix);
	dataPtr.projection = XMMatrixTranspose(projectionMatrix);


	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;
	
	deviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &dataPtr, 0, 0);

	// Finanly set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &g_pConstantBuffer);

	return true;
}
/////////////////
void ColorShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(g_pVertexLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(g_pVertexShader, NULL, 0);
	deviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	// Render the triangle.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}
