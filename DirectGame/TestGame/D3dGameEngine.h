#pragma once


class  D3dGameEngine
{
public:
	D3dGameEngine();
	~D3dGameEngine();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();
	IDXGISwapChain* GetSwapChain() { return m_swapChain; }
	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	ID3D11BlendState* m_blendState;
	//D3DXMATRIX m_projectionMatrix;
	//D3DXMATRIX m_worldMatrix;
	//D3DXMATRIX m_orthoMatrix;


};
