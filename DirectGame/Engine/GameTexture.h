#pragma once

//////////////////////////////////////////////////////////////////////////
// Author: Andreas Axelsson
// Copyright: Directive Games 2014-2015 - All Rights Reserved

#include "GameEngine.h"
#include <d3dx9math.h>
#include <d3d11.h>

class GameTexture
{
public:
	GameTexture();
	virtual ~GameTexture();
};

class TextureClass
{
public:
	TextureClass();
	~TextureClass();
	ID3D11ShaderResourceView* GetTexture() { return m_texture; }
	bool Initialize(ID3D11Device*, char*);
	ID3D11SamplerState* GetSampleState() { return m_sampleState; }
private:

		ID3D11ShaderResourceView* m_texture;
		ID3D11SamplerState* m_sampleState;
};


class ModelClass
{
private:


	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texcoord;
	};

	struct VS_CONSTANT_BUFFER
	{
		D3DXVECTOR4 sizeCoord;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void SetMeshBuffer(ID3D11DeviceContext*);

	int GetIndexCount();

	void InitShaders(ID3D11Device* device);
	void SetShader(ID3D11DeviceContext* context);
	void SetCBuffer(ID3D11DeviceContext* deviceContext, float, float,float ,float);
	void SetTexture(ID3D11DeviceContext* context, ID3D11ShaderResourceView* texture, ID3D11SamplerState* sampler);
	void DrawSprite(ID3D11DeviceContext* context);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer*   m_constantBuffer;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};