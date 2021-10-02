#include "ModelClass.h"

ModelClass::ModelClass()
{
	g_pVertexBuffer = 0;
	g_pIndexBuffer = 0;
	this->m_indexCount = 0;
	this->m_vertexCount = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	// Release the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	Vertex vertices[]=
	{
		{ XMFLOAT3(1.0f, 0.0f,  -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 0.0f,  -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 1.73f, -1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 0.0f,   1.0f),  XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 0.0f,   1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 1.73f,  1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
	};
	WORD indices[]=
	{
		0,1,2,

		3,5,4,

		0,5,3,
		0,2,5,

		5,2,4,
		2,1,4,

		3,4,0,
		0,4,1,
	};
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 8;

	// Set the number of indices in the index array.
	m_indexCount = 24;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	//vertexBufferDesc.MiscFlags = 0;
	//vertexBufferDesc.StructureByteStride = 0;


	ZeroMemory(&vertexData, sizeof(vertexData));
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	//vertexData.SysMemPitch = 0;
	//vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &g_pVertexBuffer);
	if (FAILED(result))
	{
		return false;
	}


	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(WORD) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	//indexBufferDesc.MiscFlags = 0;
	//indexBufferDesc.StructureByteStride = 0;

	ZeroMemory(&indexData, sizeof(indexData));
	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	//indexData.SysMemPitch = 0;
	//indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &g_pIndexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = 0;
		this->m_indexCount = 0;
	}

	// Release the vertex buffer.
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = 0;
		this->m_vertexCount = 0;
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride;
	UINT offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}