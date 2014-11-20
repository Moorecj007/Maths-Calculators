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
#include <tchar.h>
//#include <vld.h>

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
					bool bError = false;

					TCHAR * strSelected;
					int iLength = 0;
					int iListCount = SendMessage( hListBox, LB_GETCOUNT, 0, 0);

					// Checks if the list box is empty and displays identity matrices if so
					if( iListCount == 0)
					{
						// Create an identity matrix
						vector<vector<float>*>* pResultMatrix = CreateZeroMatrix(4);
						MakeIdentity( pResultMatrix);
						SetMatrix( _hDlg, 'c', pResultMatrix);
						SetMatrix( _hDlg, 'r', pResultMatrix);

						DeleteMatrix( pResultMatrix);
					}
					else
					{
						// Create Identity matrices
						vector<vector<float>*>* pRowResultMatrix = CreateZeroMatrix(4);
						vector<vector<float>*>* pColResultMatrix = CreateZeroMatrix(4);
						MakeIdentity( pRowResultMatrix);
						MakeIdentity( pColResultMatrix);

						// while the list still as items in it
						while( iListCount > 0)
						{
							iLength = SendMessage( hListBox, LB_GETTEXTLEN, (WPARAM)(iListCount - 1), 0);
							strSelected = new TCHAR[iLength + 1];
							SendMessage( hListBox, LB_GETTEXT, (WPARAM)(iListCount - 1), (LPARAM)strSelected);

							// Compare the selected string 
							if(!_tcscmp(strSelected, _T("Scale")))
							{
								// Get the Scalar Values from the Dialog Box
								wchar_t wstrTemp[100];
								GetDlgItemText( _hDlg, IDC_SCALE, wstrTemp, 100);

								// Validate that the Matrix scalars are floats
								if(		ValidateFloat( wstrTemp) )
								{
									vector<vector<float>*>* pRowScaleMatrix = Scale( _hDlg, 'r');
									vector<vector<float>*>* pColScaleMatrix = Scale( _hDlg, 'c');

									Multiply(pRowResultMatrix, pRowScaleMatrix);
									Multiply(pColResultMatrix, pColScaleMatrix);

									DeleteMatrix(pRowScaleMatrix);
									DeleteMatrix(pColScaleMatrix);
								}
								else
								{
									MessageBox( _hDlg, L"ERROR - Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
									bError = true;
								}
							}
							if(!_tcscmp(strSelected, _T("Skew")))
							{
								// Get the Skewing Values from the Dialog Box
								wchar_t wstrTempX[100];
								wchar_t wstrTempY[100];
								wchar_t wstrTempZ[100];
								GetDlgItemText( _hDlg, IDC_SKEW_X, wstrTempX, 100);
								GetDlgItemText( _hDlg, IDC_SKEW_Y, wstrTempY, 100);
								GetDlgItemText( _hDlg, IDC_SKEW_Z, wstrTempZ, 100);

								// Validate that the Matrix Skew variables are floats
								if(		ValidateFloat( wstrTempX)
									&&	ValidateFloat( wstrTempY)
									&&	ValidateFloat( wstrTempZ) )
								{
									vector<vector<float>*>* pRowSkewMatrix = Skew( _hDlg, 'r');
									vector<vector<float>*>* pColSkewMatrix = Skew( _hDlg, 'c');

									Multiply(pRowResultMatrix, pRowSkewMatrix);
									Multiply(pColResultMatrix, pColSkewMatrix);

									DeleteMatrix(pRowSkewMatrix);
									DeleteMatrix(pColSkewMatrix);	
								}
								else
								{
									MessageBox( _hDlg, L"ERROR - One or more of your Matrix Skewing Values are invalid", L"Error", MB_ICONERROR | MB_OK);
									bError = true;
								}
							}
							if(!_tcscmp(strSelected, _T("Translate")))
							{
								// Get the Translation Values from the Dialog Box
								wchar_t wstrTempX[100];
								wchar_t wstrTempY[100];
								wchar_t wstrTempZ[100];
								GetDlgItemText( _hDlg, IDC_TRANSLATION_X, wstrTempX, 100);
								GetDlgItemText( _hDlg, IDC_TRANSLATION_Y, wstrTempY, 100);
								GetDlgItemText( _hDlg, IDC_TRANSLATION_Z, wstrTempZ, 100);

								// Validate that the Matrix Translation values are floats
								if(		ValidateFloat( wstrTempX)
									&&	ValidateFloat( wstrTempY)
									&&	ValidateFloat( wstrTempZ) )
								{
									vector<vector<float>*>* pRowTranslateMatrix = Translate( _hDlg, 'r');
									vector<vector<float>*>* pColTranslateMatrix = Translate( _hDlg, 'c');

									Multiply(pRowResultMatrix, pRowTranslateMatrix);
									Multiply(pColResultMatrix, pColTranslateMatrix);

									DeleteMatrix(pRowTranslateMatrix);
									DeleteMatrix(pColTranslateMatrix);
								}
								else
								{
									MessageBox( _hDlg, L"ERROR - One or more of your Matrix translate values are invalid", L"Error", MB_ICONERROR | MB_OK);
									bError = true;
								}
							}
								if(!_tcscmp(strSelected, _T("Rotate")))
								{
									//Retrieve the Angle of rotation
									wchar_t wstrTemp[100];
									GetDlgItemText( _hDlg, IDC_ROTATION_ANGLE, wstrTemp, 100);

									if(	ValidateFloat( wstrTemp))
									{
										vector<vector<float>*>* pRowRotateMatrix = Rotate( _hDlg, 'r', g_iRadioRotation);
										vector<vector<float>*>* pColRotateMatrix = Rotate( _hDlg, 'c', g_iRadioRotation);

										Multiply(pRowResultMatrix, pRowRotateMatrix);
										Multiply(pColResultMatrix, pColRotateMatrix);

										DeleteMatrix(pRowRotateMatrix);
										DeleteMatrix(pColRotateMatrix);
									}
									else
									{
										MessageBox( _hDlg, L"ERROR - Your Angle of Rotation is invalid", L"Error", MB_ICONERROR | MB_OK);
										bError = true;
									}
							}
							if(!_tcscmp(strSelected, _T("Project")))
							{
								//Retrieve the Distance
								wchar_t wstrTemp[100];
								GetDlgItemText( _hDlg, IDC_PROJECTION_DISTANCE, wstrTemp, 100);

								if(	ValidateFloat( wstrTemp))
								{
									vector<vector<float>*>* pRowProjectMatrix = Project(_hDlg, 'c', g_iRadioProjection);
									vector<vector<float>*>* pColProjectMatrix = Project(_hDlg, 'c', g_iRadioProjection);

									Multiply(pRowResultMatrix, pRowProjectMatrix);
									Multiply(pColResultMatrix, pColProjectMatrix);

									DeleteMatrix(pRowProjectMatrix);
									DeleteMatrix(pColProjectMatrix);
								}
								else
								{
									MessageBox( _hDlg, L"ERROR - Your Projection Distance is invalid", L"Error", MB_ICONERROR | MB_OK);
									bError = true;
								}
							}
							iListCount--;
							delete strSelected;
						}

						if( !bError)
						{

							SendMessage( hListBox, LB_RESETCONTENT, 0, 0);

							// Transpose Row Matrix into Row Major for Displaying
							Transpose(pRowResultMatrix);
						}
						else
						{
							MakeIdentity(pRowResultMatrix);
							MakeIdentity(pColResultMatrix);
						}

						// Set the Matrices
						SetMatrix( _hDlg, 'r', pRowResultMatrix);
						SetMatrix( _hDlg, 'c', pColResultMatrix);

						// Delete allocated memory
						DeleteMatrix(pRowResultMatrix);
						DeleteMatrix(pColResultMatrix);
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
			case (IDC_Clear):				// Reset Button to reset the calculator back to default starting values
				{
					SendMessage( hListBox, LB_RESETCONTENT, 0, 0);
				}
				break;
			case (IDC_RESET):				// Reset Button to reset the calculator back to default starting values
				{
					InitialSetup(_hDlg);
					SendMessage( hListBox, LB_RESETCONTENT, 0, 0);

					// Set up the Radio Button Selections
					g_iRadioRotation = IDC_ROTATION_X;
					CheckRadioButton( _hDlg, IDC_ROTATION_X, IDC_ROTATION_Z, IDC_ROTATION_X);
					g_iRadioProjection = IDC_PROJECTION_X;
					CheckRadioButton( _hDlg, IDC_PROJECTION_X, IDC_PROJECTION_Z, IDC_PROJECTION_X);
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