/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Sets up the Window and DialogBox of the Quaternion Calculator Program and processes all the messages
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

#define WIN32_LEAN_AND_MEAN

// Library Includes
#include <windows.h> // Include all the windows headers.
#include <windowsx.h> // Include useful macros.
#include <string>
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
			InitialSetup( _hDlg);
			return (0);
		}
	break;
	case(WM_COMMAND):
		{
			switch(LOWORD( _wparam))
			{
			case (IDC_Q_APLUSB):	// A + B Button
				{
					AddAB( _hDlg);
				}
			break;
			case (IDC_Q_AMINUSB):	// A - B Button
				{
					Subtract( _hDlg, 'a', 'b');
				}
			break;
			case (IDC_Q_BMINUSA):	// B - A Button
				{
					Subtract( _hDlg, 'b', 'a');
				}
			break;
			case (IDC_Q_ATIMESB):	// AB Button
				{
					Multiply( _hDlg, 'a', 'b');
				}
			break;
			case (IDC_Q_BTIMESA):	// BA Button
				{
					Multiply( _hDlg, 'b', 'a');
				}
			break;
			case (IDC_Q_ADOTB):	// A . B Button
				{
					DotProduct( _hDlg);
				}
			break;
			case (IDC_Q_AMAGNITUDE):	// |A| Button
				{
					Magnitude( _hDlg, 'a', true);
				}
			break;
			case (IDC_Q_BMAGNITUDE):	// |B| Button
				{
					Magnitude( _hDlg, 'b', true);
				}
			break;
			case (IDC_Q_ACONJUGATE):	// A* Button
				{
					Conjugate( _hDlg, 'a');
				}
			break;
			case (IDC_Q_BCONJUGATE):	// B* Button
				{
					Conjugate( _hDlg, 'b');
				}
			break;
			case (IDC_Q_TA):			// A* Button
				{
					Scale( _hDlg, 'a');
				}
			break;
			case (IDC_Q_TB):			// B* Button
				{
					Scale( _hDlg, 'b');
				}
			break;
			case (IDC_Q_AINVERSE):			// A Inverse Button
				{
					Inverse( _hDlg, 'a');
				}
			break;
			case (IDC_Q_BINVERSE):			// B Inverse Button
				{
					Inverse( _hDlg, 'b');
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
	default:
		{
			break;
		}
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
	DialogBox( _hInstance, MAKEINTRESOURCE(IDD_CALCQUATERNIONS), 0, DlgProc);

	return (0);
}