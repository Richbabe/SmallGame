#include "stdafx.h"

#include "WindowsGameEngine.h"

std::shared_ptr<WindowsGameEngine>  WindowsGameEngine::Create()
{
	std::shared_ptr<WindowsGameEngine> p = std::make_shared<WindowsGameEngine >();
	return p;
}

WindowsGameEngine::WindowsGameEngine()
{
}

WindowsGameEngine::~WindowsGameEngine()
{
}

bool WindowsGameEngine::Initialize()
{
	m_D3dEngine.Initialize(ScreenWith, ScreenHeight, true, m_Hwnd, false, 0, 0);

	
	m_Input.Initialize(m_hInstance, m_Hwnd, ScreenWith, ScreenHeight);

	m_ModeClass.Initialize(m_D3dEngine.GetDevice());
	m_ModeClass.InitShaders(m_D3dEngine.GetDevice());

	m_fontClass.Initialize(m_D3dEngine.GetDevice(), m_D3dEngine.GetSwapChain());

	m_WinRation = (float)ScreenWith / ScreenHeight;

	return false;
}

void WindowsGameEngine::Shutdown()
{
}

void WindowsGameEngine::SetCustomData(void * userData)
{

}

void WindowsGameEngine::RegisterTickFunction(TickFunction callback)
{
}

void WindowsGameEngine::Clear()
{
}

void WindowsGameEngine::BeginScene()
{
	m_D3dEngine.BeginScene(0, 0, 0, 0);
}

void WindowsGameEngine::DrawString(float x, float y, const wchar_t * text)
{
	std::shared_ptr<FontNode> fn = std::make_shared<FontNode>();

	fn->SetText(text);
	fn->SetPosX(x);
	fn->SetPosY(y);
	fn->SetSizeX(1);
	fn->SetSizeY(1);
	m_fonNode.push_back(fn);
}

void WindowsGameEngine::DrawSprite(float x, float y, GameTexture * texture)
{
	std::shared_ptr<SpriteNode> sprite = std::make_shared<SpriteNode>();
	std::shared_ptr<GameTexture> spriteText(texture);
	sprite->SetTexture(spriteText);
	sprite->SetPosX(x);
	sprite->SetPosY(y);
	sprite->SetSizeX(texture->GetTextureSizeX());
	sprite->SetSizeY(texture->GetTexureSizeY());
	m_Node.push_back(sprite);
}

void WindowsGameEngine::EndScene()
{
	m_D3dEngine.EndScene();
}

std::shared_ptr<GameTexture> WindowsGameEngine::LoadTexture(const wchar_t * fileName)
{
	char* m_char = WcharToChar(fileName);
	auto it = m_textureMap.find(std::string(m_char));
	if (it != m_textureMap.end())
	{
		delete[] m_char;
		return std::shared_ptr<GameTexture>();
	}
	std::shared_ptr<GameTexture> texture = std::make_shared<GameTexture>();
	bool ret = texture->Initialize(m_D3dEngine.GetDevice(), m_char);
	
	if (ret)
	{
		m_textureMap.insert(std::make_pair(std::string(m_char), texture));
		delete[] m_char;
		return texture;
	}
	delete[] m_char;
	return std::shared_ptr<GameTexture>();
}

int WindowsGameEngine::Run()
{
	for (;;)
	{
		BeginScene();
		m_ModeClass.SetMeshBuffer(m_D3dEngine.GetDeviceContext());
		m_ModeClass.SetShader(m_D3dEngine.GetDeviceContext());

		for each (auto var in m_Node)
		{
			m_ModeClass.SetCBuffer(m_D3dEngine.GetDeviceContext(), var->GetSizeX(), var->GetSizeY()*m_WinRation, var->GetPosX(), var->GetPosY());
			m_ModeClass.DrawSprite(m_D3dEngine.GetDeviceContext());
		}

		m_fontClass.Draw(m_fonNode);

		m_Input.Frame();
		m_Key = m_Input.GetApplicationKeyCode();
		EndScene();
	}
	return 0;
}

bool WindowsGameEngine::IsKeyPressed(KeyCode keyCode) const
{
	return keyCode == m_Key;
}


void WindowsGameEngine::Pause()
{
	m_Pause = true;
}

void WindowsGameEngine::Resume()
{
	m_Pause = false;
}

bool WindowsGameEngine::IsPaused() const
{
	return m_Pause;
}

bool WindowsGameEngine::CreateAppWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	//Registering the Window Class
	m_hInstance = hInstance;
	m_Wc.cbSize = sizeof(WNDCLASSEX);
	m_Wc.style = 0;
	m_Wc.lpfnWndProc = WndProc;
	m_Wc.cbClsExtra = 0;
	m_Wc.cbWndExtra = 0;
	m_Wc.hInstance = hInstance;
	m_Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_Wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_Wc.lpszMenuName = NULL;
	m_Wc.lpszClassName = GameName;
	m_Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_Wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	// Creating the Window
	m_Hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		GameName,
		"GameApplicationWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, ScreenWith, ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (m_Hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	ShowWindow(m_Hwnd, nCmdShow);
	UpdateWindow(m_Hwnd);
	return true;
}



LRESULT WindowsGameEngine::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	return LRESULT();
}


