#pragma once

//////////////////////////////////////////////////////////////////////////
// Author: Andreas Axelsson
// Copyright: Directive Games 2014-2015 - All Rights Reserved

#include <memory>

#include "GameEngineTypes.h"


//
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

class GameTexture;
class D3dGameEngine;

#ifdef ENGINE_EXPORTS
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

class ENGINE_API GameEngine
{
public:
	static std::shared_ptr<GameEngine> Create();

	GameEngine();
	GameEngine(const GameEngine& other) = delete;

	virtual ~GameEngine();

	// Initialization
	/**
	 * Initialize the game engine. You must call this once after calling Create()
	 */
	virtual bool Initialize() = 0;
	/**
	 * You must call Shutdown() before exiting the application.
	 */
	virtual void Shutdown() = 0;

	// Config
	/**
	 * Register a custom data pointer that will be passed into the
	 * tick function for each update.
	 */
	virtual void SetCustomData(void* userData) = 0;
	/**
	 * Register the function you want the game to call every frame.
	 */
	virtual void RegisterTickFunction(TickFunction callback) = 0;

	// Rendering
	virtual void Clear() = 0;
	/**
	 * Call BeginScene() before any rendering.
	 */
	virtual void BeginScene() = 0;
	virtual void DrawString(float x, float y, const wchar_t* text) = 0;
	virtual void DrawSprite(float x, float y, GameTexture* texture) = 0;
	/**
	 * Call EndScene() to commit your draw calls to the scene.
	 */
	virtual void EndScene() = 0;

	// Resource management
	virtual std::shared_ptr<GameTexture> LoadTexture(const wchar_t* fileName) = 0;

	// Execution
	/**
	 * Call Run() to run the game. It will handle all keyboard reading, window management,
	 * and drawing calls for you. Every frame it will call the function you provide through
	 * RegisterTickFunction(). Run will return once the game window is closed.
	 */
	virtual int Run() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual bool IsPaused() const = 0;

	// Input
	virtual bool IsKeyPressed(KeyCode keyCode) const = 0;


};

class  D3dGameEngine
{
public:
	D3dGameEngine();
	~D3dGameEngine();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

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
