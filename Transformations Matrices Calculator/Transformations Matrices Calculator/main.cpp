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
			return (0);
		}
	break;
	case(WM_COMMAND):
		{
			// Getting index of combo selection
			HWND hComboBox = GetDlgItem( _hDlg, IDC_COMBO_SELECTION);
			int iComboIndex = SendMessage( hComboBox, CB_GETCURSEL, 0, 0);

			if(iComboIndex == 2)
			{
				// Scalar Values to change if scale is selected
				wchar_t strTempX[100];
				wchar_t strTempY[100];
				wchar_t strTempZ[100];
				GetDlgItemText( _hDlg, IDC_SCALE_X, strTempX, 100);
				GetDlgItemText( _hDlg, IDC_SCALE_Y, strTempY, 100);
				GetDlgItemText( _hDlg, IDC_SCALE_Z, strTempZ, 100);

				if(		ValidateFloat(strTempX)
					&&	ValidateFloat(strTempY)
					&&	ValidateFloat(strTempZ) )
				{

					float fX = WideStringToFloat(strTempX);
					float fY = WideStringToFloat(strTempY);
					float fZ = WideStringToFloat(strTempZ);

					string strX = FloatToString(fX);
					string strY = FloatToString(fY);
					string strZ = FloatToString(fZ);

					// While Scale is selected any change in Scale/Skew edit controls will be reflected in all three
					if( HIWORD(_wparam) == EN_CHANGE && LOWORD(_wparam) == IDC_SCALE_X)
					{
						if(fY != fX)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Y , strX.c_str()); 
						}
						if( fZ != fX)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Z , strX.c_str()); 
						}
					}
					else if( HIWORD(_wparam) == EN_CHANGE && LOWORD(_wparam) == IDC_SCALE_Y)
					{
						if(fX != fY)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_X , strY.c_str()); 
						}
						if( fZ != fY)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Z , strY.c_str()); 
						}	
					}
					else if( HIWORD(_wparam) == EN_CHANGE && LOWORD(_wparam) == IDC_SCALE_Z)
					{
						if(fX != fZ)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_X , strZ.c_str()); 
						}
						if( fY != fZ)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Y , strZ.c_str()); 
						}
					}

					// Change all scale values to the X value when Scale is selected
					if( HIWORD(_wparam) == CBN_CLOSEUP)
					{
						if(fY != fX)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Y , strX.c_str()); 
						}
						if( fZ != fX)
						{
							SetDlgItemTextA( _hDlg, IDC_SCALE_Z , strX.c_str()); 
						}
					}
				}
				else
				{
					MessageBox( _hDlg, L"ERROR - One or more of your Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
				}
			}

			switch(LOWORD( _wparam))
			{
			case (IDC_COMPUTE):				// Compute button to trigger the calculation specified in the drop down combo box
				{
					// Computes only if checkbox for matrix is unchecked
					if( !(SendDlgItemMessage( _hDlg, IDC_HOLD_COLUMN, BM_GETCHECK, 0, 0)) )
					{
						switch( iComboIndex)
						{
						case (0):
							{
								//Project(_hDlg, 'c');
							}
							break;
						case (1):
							{
								//Rotate(_hDlg, 'c');
							}
							break;
						case (2):
							{
								Scale(_hDlg, 'c');
							}
							break;
						case (3):
							{
								Skew(_hDlg, 'c');
							}
							break;
						case (4):
							{
								//Translate(_hDlg, 'c');
							}
							break;
							default: break;
						}	// End Switch	
					}

					// Computes only if checkbox for matrix is unchecked
					if( !(SendDlgItemMessage( _hDlg, IDC_HOLD_ROW, BM_GETCHECK, 0, 0)) )
					{
						switch( iComboIndex)
						{
						case (0):
							{
								//Project(_hDlg, 'r');
							}
							break;
						case (1):
							{
								//Rotate(_hDlg, 'r');
							}
							break;
						case (2):
							{
								Scale(_hDlg, 'r');
							}
							break;
						case (3):
							{
								Skew(_hDlg, 'r');
							}
							break;
						case (4):
							{
								//Translate(_hDlg, 'r');
							}
							break;
							default: break;
						}	// End Switch	
					}	

					// No Transformation was selected
					if( iComboIndex == (-1))
					{
						MessageBox( _hDlg, L"ERROR - No Transformation selected", L"Error", MB_ICONSTOP | MB_OK);
					}
				}
				break;
			case (IDC_RESET):				// Reset Button to reset the calculator back to default starting values
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
	DialogBox( _hInstance, MAKEINTRESOURCE(IDD_TRANSFORMATIONS), 0, DlgProc);

	return (0);
}