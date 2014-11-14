/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Sets up the Window and DialogBox of the Gaussian Eliminator Calculator Program and processes all the messages
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

#define WIN32_LEAN_AND_MEAN

// Library Includes
#include <windows.h>		// Include all the windows headers.
#include <windowsx.h>		// Include useful macros.
#include <string>
#include "resource.h"
//#include <vld.h>

// Local Includes
#include "resource.h"
#include "calculations.h"

// Prototypes
BOOL CALLBACK DlgProc(HWND _hDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam);

/***********************
* DlgProc: Process the Dialog Box commands
* @author: Callan Moore
* @Parameter: _hWnd: Handle to the Dialog Box
* @Parameter: _uiMsg: The message ID being sent
* @Parameter: _wParam: Additional detail about the message being sent
* @Parameter: _lParam: Additional detail about the message being sent
* @return: BOOL: Boolean Result
********************/
BOOL CALLBACK DlgProc(HWND _hDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	static HWND hEditBox = 0;
	switch(_msg)
	{
	case(WM_INITDIALOG):
		{
			InitialSetup(_hDlg);
			return (0);
		}
	break;
	case(WM_COMMAND):
		{
			switch(LOWORD( _wparam))
			{
			case (IDC_APPLY_MULTIPLY):	// Apply Button for multiplying a row by a scalar
				{
					Multiply( _hDlg);
				}
			break;
			case (IDC_APPLY_SWAP):		// Apply Button for Swapping two rows around
				{
					Swap( _hDlg);
				}
			break;
			case (IDC_APPLY_ADD):		// Apply Button for Adding a scaled row to another
				{
					Add( _hDlg);
				}
			break;
			case (IDC_RESET):			// Reset Button to reset the calculator back to default starting values
				{
					InitialSetup(_hDlg);
				}
				break;
			default: break;
			}	// End Switch
		}
		break;
	case(WM_CLOSE):
		{
			switch( MessageBox( _hDlg, L"Are you sure you would like to close the calculator?", L"Exit", MB_ICONQUESTION | MB_YESNO))
			{
			case (IDYES):
				{
					// Quit out of the whole application if dialog box is closed
					PostQuitMessage(0);
					return true; 
				}
			break;
			case (IDNO): // Do Nothing -> Fall Through
			default: break;
			} // End Switch	
		}
	break;
	default: break;
	}	// End Switch
	return false;
}

/***********************
* WinMain: Initialises the program to start
* @author: Callan Moore
* @Parameter: _hInstance: Instance handle that Windows generates for your application
* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments 
* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
* @return: int: Program ends here
********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	DialogBox( _hInstance, MAKEINTRESOURCE(IDD_GAUSSIAN_ELIMINATOR), 0, DlgProc);

	return (0);
}