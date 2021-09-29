#pragma once

#include <d3d11.h>
//#include <D3DX10math.h>
#include <xnamath.h>


class ModelClass
{
private:
	struct Vertex
	{
		//D3DXVECTOR3 position;
		//D3DXVECTOR4 color;
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer* g_pVertexBuffer;
	ID3D11Buffer* g_pIndexBuffer;
	int m_vertexCount, m_indexCount;
};

