/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Sets up the Window and DialogBox of the Transformations Calculator Program and processes all the messages
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

#define WIN32_LEAN_AND_MEAN

// Library Includes
#include <windows.h>	// Include all the windows headers.
#include <windowsx.h>	// Include useful macros.
#include <string>
#include <vld.h>

// Local Includes
#include "resource.h"
#include "calculations.h"

// Global Variable
int g_iRadioRotation;
int g_iRadioProjection;

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
	CheckRadioButton( _hDlg, IDC_ROTATION_X, IDC_ROTATION_Z, g_iRadioRotation);
	CheckRadioButton( _hDlg, IDC_PROJECTION_X, IDC_PROJECTION_Z, g_iRadioProjection);

	switch(_msg)
	{
	case(WM_INITDIALOG):
		{
			InitialSetup( _hDlg);

			// Populate the Combo box with items
			HWND hCombo = GetDlgItem( _hDlg, IDC_COMBO_SELECTION);
			SendMessage( hCombo, CB_ADDSTRING, 0, (LPARAM)L"Scale");
			SendMessage( hCombo, CB_ADDSTRING, 0, (LPARAM)L"Skew");
			SendMessage( hCombo, CB_ADDSTRING, 0, (LPARAM)L"Translate");
			SendMessage( hCombo, CB_ADDSTRING, 0, (LPARAM)L"Rotate");
			SendMessage( hCombo, CB_ADDSTRING, 0, (LPARAM)L"Project");

			// Setup the Radio Selections
			g_iRadioRotation = IDC_ROTATION_X;
			CheckRadioButton( _hDlg, IDC_ROTATION_X, IDC_ROTATION_Z, IDC_ROTATION_X);
			g_iRadioProjection = IDC_PROJECTION_X;
			CheckRadioButton( _hDlg, IDC_PROJECTION_X, IDC_PROJECTION_Z, IDC_PROJECTION_X);

			return (0);
		}
	break;
	case(WM_COMMAND):
		{
			// Getting index of combo selection
			HWND hComboBox = GetDlgItem( _hDlg, IDC_COMBO_SELECTION);
			HWND hListBox = GetDlgItem( _hDlg, IDC_LISTBOX);
			int iComboIndex = SendMessage( hComboBox, CB_GETCURSEL, 0, 0);
			

			switch(LOWORD( _wparam))
			{
			case (IDC_COMPUTE):			// Compute button to trigger the calculation specified in the drop down combo box
				{
					// Checks if the list box is empty and displays identity matrices if so
					int iInitialListCount = SendMessage( hListBox, LB_GETCOUNT, 0, 0);

					if( iInitialListCount == 0)
					{
						vector<vector<float>*>* pIdentity = CreateZeroMatrix(4);
						MakeIdentity( pIdentity);

						SetMatrix( _hDlg, 'c', pIdentity);
						SetMatrix( _hDlg, 'r', pIdentity);

						DeleteMatrix( pIdentity);
					}
					else
					{
						// while the list still as items in it
						while( iInitialListCount > 0)
						{

						}
					}

					//switch( iComboIndex)
					//{
					//case (0):
					//	{
					//		// Retrieve the Distance
					//		wchar_t wstrTemp[100];
					//		GetDlgItemText( _hDlg, IDC_PROJECTION_DISTANCE, wstrTemp, 100);

					//		if(	ValidateFloat( wstrTemp))
					//		{
					//			Project(_hDlg, 'c', g_iRadioProjection);
					//			Project(_hDlg, 'r', g_iRadioProjection);
					//		}
					//		else
					//		{
					//			MessageBox( _hDlg, L"ERROR - Your Projection Distance is invalid", L"Error", MB_ICONERROR | MB_OK);
					//		}
					//	}
					//	break;
					//case (1):
					//	{
					//		// Retrieve the Angle of rotation
					//		wchar_t wstrTemp[100];
					//		GetDlgItemText( _hDlg, IDC_ROTATION_ANGLE, wstrTemp, 100);

					//		if(	ValidateFloat( wstrTemp))
					//		{
					//			Rotate(_hDlg, 'c', g_iRadioRotation);
					//			Rotate(_hDlg, 'r', g_iRadioRotation);
					//		}
					//		else
					//		{
					//			MessageBox( _hDlg, L"ERROR - Your Angle of Rotation is invalid", L"Error", MB_ICONERROR | MB_OK);
					//		}
					//	}
					//	break;
					//case (2):
					//	{
					//		// Get the Scalar Values from the Dialog Box
					//		wchar_t wstrTemp[100];
					//		GetDlgItemText( _hDlg, IDC_SCALE, wstrTemp, 100);

					//		// Validate that the Matrix scalars are floats
					//		if(		ValidateFloat( wstrTemp) )
					//		{
					//			Scale(_hDlg, 'c');
					//			Scale(_hDlg, 'r');
					//		}
					//		else
					//		{
					//			MessageBox( _hDlg, L"ERROR - Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
					//		}
					//	}
					//	break;
					//case (3):
					//	{
					//		// Get the Skewing Values from the Dialog Box
					//		wchar_t wstrTempX[100];
					//		wchar_t wstrTempY[100];
					//		wchar_t wstrTempZ[100];
					//		GetDlgItemText( _hDlg, IDC_SKEW_X, wstrTempX, 100);
					//		GetDlgItemText( _hDlg, IDC_SKEW_Y, wstrTempY, 100);
					//		GetDlgItemText( _hDlg, IDC_SKEW_Z, wstrTempZ, 100);

					//		// Validate that the Matrix Skew variables are floats
					//		if(		ValidateFloat( wstrTempX)
					//			&&	ValidateFloat( wstrTempY)
					//			&&	ValidateFloat( wstrTempZ) )
					//		{
					//			Skew(_hDlg, 'c');
					//			Skew(_hDlg, 'r');	
					//		}
					//		else
					//		{
					//			MessageBox( _hDlg, L"ERROR - One or more of your Matrix Skewing Values are invalid", L"Error", MB_ICONERROR | MB_OK);
					//		}
					//	}
					//	break;
					//case (4):
					//	{
					//		// Get the Translation Values from the Dialog Box
					//		wchar_t wstrTempX[100];
					//		wchar_t wstrTempY[100];
					//		wchar_t wstrTempZ[100];
					//		GetDlgItemText( _hDlg, IDC_TRANSLATION_X, wstrTempX, 100);
					//		GetDlgItemText( _hDlg, IDC_TRANSLATION_Y, wstrTempY, 100);
					//		GetDlgItemText( _hDlg, IDC_TRANSLATION_Z, wstrTempZ, 100);

					//		// Validate that the Matrix Translation values are floats
					//		if(		ValidateFloat( wstrTempX)
					//			&&	ValidateFloat( wstrTempY)
					//			&&	ValidateFloat( wstrTempZ) )
					//		{
					//			Translate(_hDlg, 'c');
					//			Translate(_hDlg, 'r');
					//		}
					//		else
					//		{
					//			MessageBox( _hDlg, L"ERROR - One or more of your Matrix translate values are invalid", L"Error", MB_ICONERROR | MB_OK);
					//		}
					//	}
					//	break;
					//default: break;
					//}	// End Switch	

					// No Transformation was selected
					if( iComboIndex == (-1))
					{
						MessageBox( _hDlg, L"ERROR - No Transformation selected", L"Error", MB_ICONSTOP | MB_OK);
					}
				}
				break;
			case (IDC_ROTATION_X):	// Fall Through
			case (IDC_ROTATION_Y):	// Fall Through
			case (IDC_ROTATION_Z):	
				{
					g_iRadioRotation = LOWORD(_wparam);
					CheckRadioButton( _hDlg, IDC_ROTATION_X, IDC_ROTATION_Z, LOWORD( _wparam));
				}
				break;
			case (IDC_PROJECTION_X):	// Fall Through
			case (IDC_PROJECTION_Y):	// Fall Through
			case (IDC_PROJECTION_Z):	
				{
					g_iRadioProjection = LOWORD(_wparam);
					CheckRadioButton( _hDlg, IDC_PROJECTION_X, IDC_PROJECTION_Z, LOWORD(_wparam));
				}
				break;
			case (IDC_RESET):				// Reset Button to reset the calculator back to default starting values
				{
					InitialSetup(_hDlg);
				}
				break;
			case (IDC_COMBO_SELECTION):
				{
					if( HIWORD(_wparam) == CBN_SELENDOK)
					{
						wchar_t wstrTemp[100];
						HWND hComboBox = GetDlgItem( _hDlg, IDC_COMBO_SELECTION);
						HWND hListBox = GetDlgItem( _hDlg, IDC_LISTBOX);
						SendMessage(hComboBox, WM_GETTEXT, 100, LPARAM(wstrTemp));

						SendMessage(hListBox, LB_ADDSTRING, 100, LPARAM(wstrTemp));
					}
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
	DialogBox( _hInstance, MAKEINTRESOURCE(IDD_TRANSFORMATIONS), 0, DlgProc);

	return (0);
}