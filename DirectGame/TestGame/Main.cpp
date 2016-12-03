#include "stdafx.h"
#include <windows.h>
#include <timeapi.h>

//#include "GameEngine.h"
#include "WindowsGameEngine.h"

std::shared_ptr<GameEngine> g_gameEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

#ifdef WindowPlatform
	g_gameEngine = WindowsGameEngine::Create();
	WindowsGameEngine* windowEngin = (WindowsGameEngine*)g_gameEngine.get();
	windowEngin->CreateAppWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

#endif

	g_gameEngine->Initialize();

#ifdef WindowPlatform
	//timeBeginPeriod(1);
	return g_gameEngine->Run();
	//timeEndPeriod(1);
#endif

#if 0

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	//Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"GameApplicationWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, ScreenWith, ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

#endif	




#if 0
	gD3dEngine.Initialize(ScreenWith, ScreenHeight,true,hwnd,false,0,0);

	ModelClass quadModel;
	quadModel.Initialize(gD3dEngine.GetDevice());
	quadModel.InitShaders(gD3dEngine.GetDevice());

	TextureClass texData1;
	texData1.Initialize(gD3dEngine.GetDevice(),"Resources/ship.png");

	TextureClass texData2;
	texData2.Initialize(gD3dEngine.GetDevice(), "Resources/Bomb.png");

	InputClass input;
	input.Initialize(hInstance, hwnd, ScreenWith, ScreenHeight);
	
	float winRation = (float)ScreenWith / ScreenHeight;
	

	bool done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		// If windows signals to end the application then exit out.
		if (Msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			gD3dEngine.BeginScene(0, 0, 0, 0);

			quadModel.SetMeshBuffer(gD3dEngine.GetDeviceContext());
			quadModel.SetCBuffer(gD3dEngine.GetDeviceContext(), 0.1, 0.1*winRation, 0, 0);

			quadModel.SetShader(gD3dEngine.GetDeviceContext());
			quadModel.SetTexture(gD3dEngine.GetDeviceContext(), texData1.GetTexture(), texData1.GetSampleState());

			static float pos = 0;
			static float vel = 0.01f;

			pos += vel;
			if (abs(pos) > 0.95)
			{
				vel *= -1;
			}

			float sizX = 0.1f, sizeY = 0.1f;

			quadModel.SetCBuffer(gD3dEngine.GetDeviceContext(), sizX, sizeY*winRation, pos, 0);
			quadModel.DrawSprite(gD3dEngine.GetDeviceContext());


			quadModel.SetTexture(gD3dEngine.GetDeviceContext(), texData2.GetTexture(), texData2.GetSampleState());
			for (vector)
			{
			
			quadModel.SetCBuffer(gD3dEngine.GetDeviceContext(), 0.1, 0.1, pos, 0.5);
			quadModel.DrawSprite(gD3dEngine.GetDeviceContext());
			}
			gD3dEngine.EndScene();

			input.Frame();

		}

	}
#endif

//	return Msg.wParam;
}