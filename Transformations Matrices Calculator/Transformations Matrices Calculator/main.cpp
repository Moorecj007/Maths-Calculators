/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Sets up the Window and DialogBox of the Transformation Matrices Calculator Program and processes all the messages
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Include all the windows headers.
#include <windowsx.h> // Include useful macros.
#include <string>
#include "resource.h"

#define WINDOW_CLASS_NAME L"TRANSFORMATIONCALCULATOR"

// Global Variables
HINSTANCE g_hInstance;

// Prototypes
BOOL CALLBACK DlgProc(HWND _hDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam);
LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

BOOL CALLBACK DlgProc(HWND _hDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	static HWND hEditBox = 0;
	switch(_msg)
	{
	case(WM_INITDIALOG):
		{
			
			return (0);
		}
	break;
	case(WM_COMMAND):
		{
			switch(LOWORD( _wparam))
			{
			break;
			default:
				{
					break;
				}
			}	// End Switch
		}
		break;
	case(WM_CLOSE):
		{
			// Quit out of the whole application if dialog box is closed
			PostQuitMessage(0);
			return true; 
			break;
		}
	default:
		{
			break;
		}
	}	// End Switch
	return false;
}

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	PAINTSTRUCT ps;		// Used in WM_PAINT.
	HDC hdc;			// Handle to a device context.

	// Switch case dependent on the message sent
	switch (_msg)
	{
		case WM_CREATE:
		{
			DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_TRANSFORMATIONS), 0, DlgProc);
			return (0);
		}
		break;
		case WM_PAINT:
		{
			
			hdc = BeginPaint(_hwnd, &ps);
			EndPaint(_hwnd, &ps);
			
			return (0);
		}
		break;
		case WM_DESTROY:
		{
			// Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);
			return (0);
		}
		break;
		case WM_COMMAND:
		{

		}
		break;
		default:break;
	} // End switch.

	// Process any messages left to process
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	WNDCLASSEX winclass;	// This will hold the class we create.
	HWND hwnd;				// Generic window handle.
	MSG msg;				// Generic message.

	// Sets the global instance to the current instance
	g_hInstance = _hInstance;

	// Fills in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// Registers the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	hwnd = CreateWindowEx(NULL,			// Extended style.
	WINDOW_CLASS_NAME,					// Class.
	L"Transformation Matrices Calculator",				// Title.
	WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	0, 0,								// Initial x,y.
	400, 400,							// Initial width, height.
	NULL,								// Handle to parent.
	NULL,								// Handle to menu.
	_hInstance,							// Instance of this application.
	NULL);								// Extra creation parameters.

	// Check the window was created successfully.
	if (!hwnd)
	{
		return (0);
	}

	// Enter main event loop.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Translate any accelerator keys...
		TranslateMessage(&msg);
		// Send the message to the window proc.
		DispatchMessage(&msg);
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}