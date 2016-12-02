#include "stdafx.h"
#include "GameEngine.h"
#include <windows.h>
#include "GameTexture.h"
#include "FontClass.h"

#include "InputClass.h"

const char g_szClassName[] = "GameApplicatioon";

#define ScreenWith 800
#define ScreenHeight 600
D3dGameEngine gD3dEngine;

//the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
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

	gD3dEngine.Initialize(ScreenWith, ScreenHeight,true,hwnd,false,0,0);
	FontClass font;
	font.Initialize(gD3dEngine.GetDevice(),gD3dEngine.GetSwapChain());

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

			ID3D11Resource* res;
			texData1.GetTexture()->GetResource(&res);
			ID3D11Texture2D* tex = (ID3D11Texture2D*) res;
			D3D11_TEXTURE2D_DESC desc;
			tex->GetDesc(&desc);

			static float pos = 0;
			static float vel = 0.01f;
		
			pos += vel;
			if (abs(pos) > 0.95)
			{
				vel *= -1;
			}

			float sizX=0.1f, sizeY=0.1f;

			float sizeXX = (float)desc.Width / (2 * ScreenWith);
			float sizeYY = (float)desc.Height / (2 * ScreenHeight);
			quadModel.SetCBuffer(gD3dEngine.GetDeviceContext(), sizeXX, sizeYY*winRation, pos, 0);
			quadModel.DrawSprite(gD3dEngine.GetDeviceContext());


			quadModel.SetTexture(gD3dEngine.GetDeviceContext(), texData2.GetTexture(), texData2.GetSampleState());
			quadModel.SetCBuffer(gD3dEngine.GetDeviceContext(), 0.1, 0.1, pos, 0.5);
			quadModel.DrawSprite(gD3dEngine.GetDeviceContext());

			font.Draw();
			gD3dEngine.EndScene();

			input.Frame();

		}

	}

	return Msg.wParam;
}