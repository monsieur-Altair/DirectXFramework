#pragma once

#include <d3d11.h>
#include <xnamath.h>
#include "TextureClass.h"

class ModelClass
{

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	int GetIndexCount();
	bool Initialize(ID3D11Device*,WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	ID3D11ShaderResourceView* GetTexture();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	struct Vertex
	{
		XMFLOAT3 Pos;
		//XMFLOAT4 Color;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
	};

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	ID3D11Buffer* g_pVertexBuffer;
	ID3D11Buffer* g_pIndexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;
};

