#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "GameEngine.h"
#include "D3dGameEngine.h"
#include "InputClass.h"
#include "GameTexture.h"
#include "SpriteNode.h"
#include <map>
#include <vector>

#include "Common.h"
#include "FontClass.h"

class WindowsGameEngine : public GameEngine {
public:

	static std::shared_ptr<WindowsGameEngine> Create();


	WindowsGameEngine();

	virtual ~WindowsGameEngine();

	// Initialization
	/**
	* Initialize the game engine. You must call this once after calling Create()
	*/
	virtual bool Initialize();
	/**
	* You must call Shutdown() before exiting the application.
	*/
	virtual void Shutdown();

	// Config
	/**
	* Register a custom data pointer that will be passed into the
	* tick function for each update.
	*/
	virtual void SetCustomData(void* userData);
	/**
	* Register the function you want the game to call every frame.
	*/
	virtual void RegisterTickFunction(TickFunction callback);

	// Rendering
	virtual void Clear();
	/**
	* Call BeginScene() before any rendering.
	*/
	virtual void BeginScene();
	virtual void DrawString(float x, float y, const wchar_t* text);
	virtual void DrawSprite(float x, float y, GameTexture* texture);
	/**
	* Call EndScene() to commit your draw calls to the scene.
	*/
	virtual void EndScene();

	// Resource management
	virtual std::shared_ptr<GameTexture> LoadTexture(const wchar_t* fileName) ;

	// Execution
	/**
	* Call Run() to run the game. It will handle all keyboard reading, window management,
	* and drawing calls for you. Every frame it will call the function you provide through
	* RegisterTickFunction(). Run will return once the game window is closed.
	*/
	virtual int Run() ;

	// Input
	virtual bool IsKeyPressed(KeyCode keyCode) const;


	virtual void Pause();
	virtual void Resume();
	virtual bool IsPaused() const;

	// create window sreen
	bool CreateAppWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow);

	

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	char* WcharToChar(const wchar_t* wp)
	{
		char *m_char;
		int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
		m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		return m_char;
	}

private:
	D3dGameEngine m_D3dEngine;

	InputClass m_Input;
	bool m_Pause;
	ModelClass m_ModeClass;

	FontClass m_fontClass;

	KeyCode m_Key;
	float m_WinRation;

	//windows
	WNDCLASSEX m_Wc;
	HWND m_Hwnd;
	HINSTANCE m_hInstance;

	const char GameName[128] = "GameName";

	std::map<std::string, std::shared_ptr<GameTexture>> m_textureMap;

	std::vector<std::shared_ptr<SpriteNode> > m_Node;

	std::vector<std::shared_ptr<FontNode>> m_fonNode;
};
