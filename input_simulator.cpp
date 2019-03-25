#include "input_simulator.h"

#include <Windows.h>
#include <queue>

#include "Debug.h"

InputSimulator::InputSimulator()
{
	MouseMoveState = false;
	LastCursorPos.x = 0;
	LastCursorPos.y = 0;
}


int InputSimulator::CharToVK(wchar_t input)
{
	switch (input)
	{
	case '1':
		return 0x31;
		break;
	case '2':
		return 0x32;
		break;
	case '3':
		return 0x33;
		break;
	case '4':
		return 0x34;
		break;
	case '5':
		return 0x35;
		break;
	case '6':
		return 0x36;
		break;
	case '7':
		return 0x37;
		break;
	case '8':
		return 0x38;
		break;
	case '9':
		return 0x39;
		break;
	case 'q':
		return 0x51;
		break;
	case 'w':
		return 0x57;
		break;
	case 'e':
		return 0x45;
		break;
	case 'r':
		return 0x52;
		break;
	case 'a':
		return 0x41;
		break;
	case 's':
		return 0x53;
		break;
	case 'd':
		return 0x44;
		break;
	case 'f':
		return 0x46;
		break;
	case 'u':
		return 0x55;
		break;
	}
	return 0;
}

void InputSimulator::SendKeyOrMouse(wchar_t input)
{
	switch (input)
	{
	case 'L':
		SendMouse(Left);
		break;
	case 'R':
		SendMouse(Right);
		break;
	default:
		SendKey(input);
		break;
	}
}

void InputSimulator::SendKeyOrMouseWithoutMove(wchar_t input)
{
	switch (input)
	{
	case 'L':
		SendMouseWithoutMove(Left);
		break;
	case 'R':
		SendMouseWithoutMove(Right);
		break;
	default:
		SendKey(input);
		break;
	}
}

void InputSimulator::SendKey(int key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputSimulator::SendKey(wchar_t key)
{
	SendKey(CharToVK(key));
}

void InputSimulator::SendKeyDown(int key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputSimulator::SendKeyDown(wchar_t key)
{
	SendKeyDown(CharToVK(key));
}

void InputSimulator::SendKeyUp(int key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputSimulator::SendKeyUp(wchar_t key)
{
	SendKeyUp(CharToVK(key));
}

void SendKeyUp(int key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void InputSimulator::SendMouse(MouseClick Click)
{
	INPUT ip;

	if (Click == Left)//hold force stand still
	{
		SendKeyDown(VK_SHIFT);
	}

	ZeroMemory(&ip, sizeof(ip));

	//POINT CursorPos;
	//GetCursorPos(&CursorPos);
	Sleep(1);
	//SetCursorPos(700, 500);
	//Sleep(1);
	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;

	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	}
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);
	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	}
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(1);
	//SetCursorPos(CursorPos.x, CursorPos.y);
	//Sleep(1);

	if (Click == Left)//hold force stand still
	{
		SendKeyUp(VK_SHIFT);
	}
}

void InputSimulator::SendMouseWithoutMove(MouseClick Click)
{
	INPUT ip;

	if (Click == Left)//hold force stand still
	{
		SendKeyDown(VK_SHIFT);
	}


	ZeroMemory(&ip, sizeof(ip));

	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;

	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	}
	SendInput(1, &ip, sizeof(INPUT));


	Sleep(1);

	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	if (Click == Left)
	{
		ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	}
	else
	{
		ip.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	}
	SendInput(1, &ip, sizeof(INPUT));
	// Set up a generic keyboard event.

	Sleep(1);

	if (Click == Left)//hold force stand still
	{
		SendKeyUp(VK_SHIFT);
	}
}

void InputSimulator::MoveMouse()
{
	if (GetAsyncKeyState(CharToVK('6'))) return;

	INPUT ip;

	ZeroMemory(&ip, sizeof(ip));

	POINT CursorPos;
	GetCursorPos(&CursorPos);

	LONG dist1 = abs(CursorPos.x - 820) + abs(CursorPos.y - 507);
	LONG dist2 = abs(CursorPos.x - 1100) + abs(CursorPos.y - 507);

	if (dist1 <= 100 || dist2 <= 100)
	{
		CursorPos = LastCursorPos;
	}

	LastCursorPos = CursorPos;
	Sleep(1);

	if (MouseMoveState)
	{
		SetCursorPos(820, 507);
	}
	else
	{
		SetCursorPos(1100, 507);
	}

	//Sleep(100);
	Sleep(10);
	MouseMoveState = !MouseMoveState;
	
	wchar_t ForceMove = TEXT('u');
	//SendKey(ForceMove);


	//////////////////////////////////////////////////////////

	ZeroMemory(&ip, sizeof(ip));

	Sleep(1);
	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
		ip.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);
	ip.type = INPUT_MOUSE;
	ip.mi.dx = 0;
	ip.mi.dy = 0;
	ip.mi.mouseData = 0;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
		ip.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
	SendInput(1, &ip, sizeof(INPUT));
	////////////////////////////////////////////////
	Sleep(1);

	SetCursorPos(CursorPos.x, CursorPos.y);
	Sleep(1);

}

InputSimulator::~InputSimulator()
{
}
