#include "stdafx.h"
#include "InputClass.h"

InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}

InputClass::InputClass(const InputClass &)
{
}

InputClass::~InputClass()
{
}

bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeigh)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeigh;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;


	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
	{
		return false;
	}


	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}


	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}


	result = m_keyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}


	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}


	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void InputClass::Shutdown()
{

	// Release the mouse.
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;

}

bool InputClass::Frame()
{
	bool result;


	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}

bool InputClass::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
	return;
}

KeyCode InputClass::GetApplicationKeyCode()
{
	if (m_keyboardState[DIK_A] & 0x80)
	{
		return KeyCode::Key_A;
	}
	else if (m_keyboardState[DIK_B] & 0x80)
	{
		return KeyCode::Key_B;
	}
	else if (m_keyboardState[DIK_C] & 0x80)
	{
		return KeyCode::Key_C;
	}
	else if (m_keyboardState[DIK_D] & 0x80)
	{
		return KeyCode::Key_D;
	}
	else if (m_keyboardState[DIK_E] & 0x80)
	{
		return KeyCode::Key_E;
	}
	else if (m_keyboardState[DIK_F] & 0x80)
	{
		return KeyCode::Key_F;
	}
	else if (m_keyboardState[DIK_G] & 0x80)
	{
		return KeyCode::Key_G;
	}
	else if (m_keyboardState[DIK_H] & 0x80)
	{
		return KeyCode::Key_H;
	}
	else if (m_keyboardState[DIK_I] & 0x80)
	{
		return KeyCode::Key_I;
	}
	else if (m_keyboardState[DIK_J] & 0x80)
	{
		return KeyCode::Key_J;
	}
	else if (m_keyboardState[DIK_K] & 0x80)
	{
		return KeyCode::Key_K;
	}
	else if (m_keyboardState[DIK_L] & 0x80)
	{
		return KeyCode::Key_L;
	}
	else if (m_keyboardState[DIK_M] & 0x80)
	{
		return KeyCode::Key_M;
	}
	else if (m_keyboardState[DIK_N] & 0x80)
	{
		return KeyCode::Key_N;
	}
	else if (m_keyboardState[DIK_O] & 0x80)
	{
		return KeyCode::Key_O;
	}
	else if (m_keyboardState[DIK_P] & 0x80)
	{
		return KeyCode::Key_P;
	}
	else if (m_keyboardState[DIK_Q] & 0x80)
	{
		return KeyCode::Key_Q;
	}
	else if (m_keyboardState[DIK_R] & 0x80)
	{
		return KeyCode::Key_R;
	}
	else if (m_keyboardState[DIK_S] & 0x80)
	{
		return KeyCode::Key_S;
	}
	else if (m_keyboardState[DIK_T] & 0x80)
	{
		return KeyCode::Key_T;
	}
	else if (m_keyboardState[DIK_U] & 0x80)
	{
		return KeyCode::Key_U;
	}
	else if (m_keyboardState[DIK_V] & 0x80)
	{
		return KeyCode::Key_V;
	}
	else if (m_keyboardState[DIK_W] & 0x80)
	{
		return KeyCode::Key_W;
	}
	else if (m_keyboardState[DIK_X] & 0x80)
	{
		return KeyCode::Key_X;
	}
	else if (m_keyboardState[DIK_Y] & 0x80)
	{
		return KeyCode::Key_Y;
	}
	else if (m_keyboardState[DIK_Z] & 0x80)
	{
		return KeyCode::Key_Z;
	}
	else if (m_keyboardState[DIK_0] & 0x80)
	{
		return KeyCode::Key_0;
	}
	else if (m_keyboardState[DIK_1] & 0x80)
	{
		return KeyCode::Key_1;
	}
	else if (m_keyboardState[DIK_2] & 0x80)
	{
		return KeyCode::Key_2;
	}
	else if (m_keyboardState[DIK_3] & 0x80)
	{
		return KeyCode::Key_3;
	}
	else if (m_keyboardState[DIK_4] & 0x80)
	{
		return KeyCode::Key_4;
	}
	else if (m_keyboardState[DIK_5] & 0x80)
	{
		return KeyCode::Key_5;
	}
	else if (m_keyboardState[DIK_6] & 0x80)
	{
		return KeyCode::Key_6;
	}
	else if (m_keyboardState[DIK_7] & 0x80)
	{
		return KeyCode::Key_7;
	}
	else if (m_keyboardState[DIK_8] & 0x80)
	{
		return KeyCode::Key_8;
	}
	else if (m_keyboardState[DIK_9] & 0x80)
	{
		return KeyCode::Key_9;
	}
	else if (m_keyboardState[DIK_LEFT] & 0x80)
	{
		return KeyCode::Key_Left;
	}
	else if (m_keyboardState[DIK_RIGHT] & 0x80)
	{
		return KeyCode::Key_Right;
	}
	else if (m_keyboardState[DIK_UP] & 0x80)
	{
		return KeyCode::Key_Up;
	}
	else if (m_keyboardState[DIK_DOWN] & 0x80)
	{
		return KeyCode::Key_Down;
	}
	else if (m_keyboardState[DIK_SPACE] & 0x80)
	{
		return KeyCode::Key_Space;
	}
	else if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return KeyCode::Key_Esc;
	}
	else if (m_keyboardState[DIK_RETURN] & 0x80)
	{
		return KeyCode::Key_Enter;
	}
	
	return KeyCode::Key_Last;
}

bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	
	

// 	if (m_keyboardState[DIK_LEFT] & 0x80)
// 	{
// 		int y = 0;
// 	}
// 
// 	if (m_keyboardState[DIK_LEFT] & 0x80)
// 	{
// 		int y = 0;
// 	}


	return true;
}

bool InputClass::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void InputClass::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_mouseX += m_mouseState.lX;
	m_mouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_mouseX < 0) { m_mouseX = 0; }
	if (m_mouseY < 0) { m_mouseY = 0; }

	if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
	if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }

	return;
}
