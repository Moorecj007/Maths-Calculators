/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.cpp 
* Description : Gaussian Elimination calculation function implementation
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

// This Includes
#include "calculations.h"

/***********************
* InitialSetup: Sets all the Text boxes to default value
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void InitialSetup(HWND _hDlg)
{
	float fDefault = 00;	// Choose zero as default starting value
	string strDefault = FloatToString(fDefault);
	string strEmpty = "";
	
	// Sets Row 1 Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_ROW1_A, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW1_B, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW1_C, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW1_D, strDefault.c_str());

	// Sets Row 2 Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_ROW2_A, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW2_B, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW2_C, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW2_D, strDefault.c_str());

	// Sets Row 3 Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_ROW3_A, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW3_B, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW3_C, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_ROW3_D, strDefault.c_str());

	// Sets Operation Edit Controls to empty
	SetDlgItemTextA( _hDlg, IDC_MULTIPLY_SCALAR, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MULTIPLY_ROW, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_SWAPROW_A, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_SWAPROW_B, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_ADD_SCALAR, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_ADD_MULIPLIEDROW, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_ADD_RECIEVINGROW, strEmpty.c_str());
}

/***********************
* Multiply: Multiplies a row by a scalar
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void Multiply(HWND _hDlg)
{
	wchar_t wstrTemp[100]; // Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion

	// Retrieve selected row
	GetDlgItemText( _hDlg, IDC_MULTIPLY_ROW, wstrTemp, 100);

	if( !ValidateInt( wstrTemp))
	{
		MessageBox( _hDlg, L"ERROR - Row Selection is Invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	int iRow = WideStringToInt(wstrTemp);

	// Float variables to hold the Row values
	float fA, fB, fC, fD;

	// Retrieve the Scalar
	GetDlgItemText( _hDlg, IDC_MULTIPLY_SCALAR, wstrTemp, 100);

	// Validate the Scalar
	if( !ValidateFloat( wstrTemp))
	{
		MessageBox( _hDlg, L"ERROR - Scalar is Invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	float fScalar = WideStringToFloat(wstrTemp);

	if( RetrieveRow( _hDlg, iRow, fA, fB, fC, fD)) // Retrieve the A, B, C, D values of the Row
	{
		// Multiply each value of the Row by the scalar
		fA *= fScalar;
		fB *= fScalar;	
		fC *= fScalar;
		fD *= fScalar;

		// Return the values to the Edit Controls to show Scaled Row.
		SetRow( _hDlg, iRow, fA, fB, fC, fD);

		// Check to see if result as achieved either Row Echelon Form
		RowEchelonCheck(_hDlg);
	}
}

/***********************
* Swap: Swaps two rows around
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void Swap(HWND _hDlg)
{
	// Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion for each Row
	wchar_t wstrTemp1[100]; 
	wchar_t wstrTemp2[100]; 

	// Retrieve selected rows
	GetDlgItemText( _hDlg, IDC_SWAPROW_A, wstrTemp1, 100);
	GetDlgItemText( _hDlg, IDC_SWAPROW_B, wstrTemp2, 100);

	// Check that both Row Selections are valid
	if(		!ValidateInt( wstrTemp1)
		||	!ValidateInt( wstrTemp2) )
	{
		MessageBox( _hDlg, L"ERROR - Row Selection is Invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	int iRow1 = WideStringToInt(wstrTemp1);
	int iRow2 = WideStringToInt(wstrTemp2);

	if( iRow1 == iRow2)
	{
		MessageBox( _hDlg, L"ERROR - You are trying to swap the same row.", L"Error", MB_ICONERROR | MB_OK);
		return;
	}

	// Float variables to hold the Row values
	float fRow1A, fRow1B, fRow1C, fRow1D;
	float fRow2A, fRow2B, fRow2C, fRow2D;

	if(		RetrieveRow( _hDlg, iRow1, fRow1A, fRow1B, fRow1C, fRow1D)		// Retrieving Row 1 Values
		&&	RetrieveRow( _hDlg, iRow2, fRow2A, fRow2B, fRow2C, fRow2D) )	// Retrieving Row 2 Values
	{
		// Set the Row Edit Controls to the other row
		SetRow( _hDlg, iRow1, fRow2A, fRow2B, fRow2C, fRow2D);
		SetRow( _hDlg, iRow2, fRow1A, fRow1B, fRow1C, fRow1D);

		// Check to see if result as achieved either Row Echelon Form
		RowEchelonCheck(_hDlg);
	}

	
}

/***********************
* Add: Adds a scaled version of one row to another
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void Add(HWND _hDlg)
{
	// Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion for each Row
	wchar_t wstrTemp1[100]; 
	wchar_t wstrTemp2[100]; 
	wchar_t wstrTempScalar[100]; 

	// Retrieve selected row
	GetDlgItemText( _hDlg, IDC_ADD_MULIPLIEDROW, wstrTemp1, 100);
	GetDlgItemText( _hDlg, IDC_ADD_RECIEVINGROW, wstrTemp2, 100);

	// Check that both Row Selections are valid
	if(		!ValidateInt( wstrTemp1)
		||	!ValidateInt( wstrTemp2) )
	{
		MessageBox( _hDlg, L"ERROR - Row Selection is Invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	int iRow1 = WideStringToInt(wstrTemp1);
	int iRow2 = WideStringToInt(wstrTemp2);

	if( iRow1 == iRow2)
	{
		MessageBox( _hDlg, L"ERROR - Trying to Add to the same row. Use the Multiply Row function if that is your intent.", L"Error", MB_ICONERROR | MB_OK);
		return;
	}

	// Retrieve the Scalar
	GetDlgItemText( _hDlg, IDC_ADD_SCALAR, wstrTempScalar, 100);
	// Validate the Scalar
	if( !ValidateFloat( wstrTempScalar))
	{
		MessageBox( _hDlg, L"ERROR - Scalar is Invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	float fScalar = WideStringToFloat(wstrTempScalar);

	// Float variables to hold the Row values
	float fRow1A, fRow1B, fRow1C, fRow1D;
	float fRow2A, fRow2B, fRow2C, fRow2D;

	if(		RetrieveRow( _hDlg, iRow1, fRow1A, fRow1B, fRow1C, fRow1D)
		&&	RetrieveRow( _hDlg, iRow2, fRow2A, fRow2B, fRow2C, fRow2D) )
	{
		fRow2A += (fScalar * fRow1A);
		fRow2B += (fScalar * fRow1B);
		fRow2C += (fScalar * fRow1C);
		fRow2D += (fScalar * fRow1D);

		SetRow( _hDlg, iRow2, fRow2A, fRow2B, fRow2C, fRow2D);

		// Check to see if result as achieved either Row Echelon Form
		RowEchelonCheck(_hDlg);
	}

	
}

/***********************
* RowEchelonCheck: Checks if the displayed matrix is of Row Echelon or Reduced Row Echelon form after computation
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void RowEchelonCheck(HWND _hDlg)
{
	bool bValidated = true;
	bool bAllowedZeroRow = true;

	// Create a blank 3X4 Matrix
	vector<vector<float>*>* pMatrix = new vector<vector<float>*>;
	for( int i = 0; i < 3; i++)
	{
		vector<float>* pVecFloatTemp = new vector<float>;
		for( int j = 0; j < 4; j++)
		{
			pVecFloatTemp->push_back(0.0f);
		}
		pMatrix->push_back(pVecFloatTemp);
	}

	// float variables to store the Row Values
	float fA, fB, fC, fD;

	for( int i = 2 ; i >= 0; i--)	// Go backwards up the rows
	{
		if( RetrieveRow( _hDlg, ( i + 1), fA, fB, fC, fD))
		{
			(*(*pMatrix)[i])[0] = fA;
			(*(*pMatrix)[i])[1] = fB;
			(*(*pMatrix)[i])[2] = fC;
			(*(*pMatrix)[i])[3] = fD;

			// Check that all the full zero rows are at the bottom
			if( (fA == 0) && (fB == 0) && (fC == 0) && (fD == 0))
			{
				if( bAllowedZeroRow == false)
				{
					DeleteMatrix(pMatrix);
					return; 
				}
			}
			else
			{
				bAllowedZeroRow = false;
			}
		}
		else
		{
			bValidated = false;
		}
	}

	if( bValidated)
	{
		int iRowAboveLeadingOneIndex = (-1);
		float fCurrentValue;
		bool bFoundReduced = true;
		bool bAllowedNonZero;

		// Reduced Row Echelon Check
		iRowAboveLeadingOneIndex = (-1);

		// Cycle through the columns
		for( int i = 0; i < 3; i++)	// Dont look at final column
		{
			bAllowedNonZero = true;
			// Cycle through the rows
			for( int j = 0; j < 3; j++)
			{
				fCurrentValue = (*(*pMatrix)[j])[i];

				if( fCurrentValue == 0)
				{
					// Move onto next column
					continue;
				}
				else if( (fCurrentValue == 1) && (i > iRowAboveLeadingOneIndex) && bAllowedNonZero)
				{
					// Found first value that is a 1 in the column ( can be the only non zero element)
					iRowAboveLeadingOneIndex = i;
					bAllowedNonZero = false;
				}
				else
				{
					if( bAllowedNonZero)
					{
						bAllowedNonZero = false;
					}
					else
					{
						// Reduced Row Echelon can no longer be obtained, break out of for loops
						bFoundReduced = false;
						break;
					}
					
				}
			}
		}
		if( bFoundReduced && iRowAboveLeadingOneIndex != (-1))
		{
			// Row Echelon has been found - Dispay Message Box
			MessageBox( _hDlg, L"You have achieved Reduced Row Echelon form", L"Congratulations", MB_ICONINFORMATION | MB_OK);
			DeleteMatrix(pMatrix);
			return; // No need to check for Row Echelon
		}

		// Row Echelon Check
		iRowAboveLeadingOneIndex = (-1);
		
		// Cycle through the rows
		for( int i = 0; i < 3; i++)
		{
			// Cycle through the columns
			for( int j = 0; j < 3; j++)	// Dont look at final column
			{
				fCurrentValue = (*(*pMatrix)[i])[j];

				if( fCurrentValue == 0)
				{
					// Go to next column
					continue;
				}
				else if( fCurrentValue != 0)
				{
					// Leading One must be in first row or to the right of the leading one above it
					if( i == 0 || j > iRowAboveLeadingOneIndex)
					{
						iRowAboveLeadingOneIndex = j;
						break;	// Go to next row
					}
					else
					{
						// Matrix can't be Row echelon so print nothing and exit function
						DeleteMatrix(pMatrix);
						return;
					}
				}
				else
				{
					// Matrix can't be Row echelon so print nothing and exit function
					DeleteMatrix(pMatrix);
					return;	
				}
			}
		}
		if( iRowAboveLeadingOneIndex != (-1) )
		{
			// Row Echelon has been found - Dispay Message Box
			MessageBox( _hDlg, L"You have achieved Row Echelon form", L"Congratulations", MB_ICONINFORMATION | MB_OK);
		}
	}
	
	DeleteMatrix(pMatrix);
}

/***********************
* DeleteMatrix: Deletes a Matrix
* @author: Callan Moore
* @parameter: vector<vector<float>*>*: Pointer to a matrix to delete
********************/
void DeleteMatrix(vector<vector<float>*>* _pMatrix)
{
	// Deleting the Rows
	while( (*_pMatrix).empty() == false )
	{
		delete (*_pMatrix).back();
		(*_pMatrix).back() = 0;
		(*_pMatrix).pop_back();
	}
	delete _pMatrix;
	_pMatrix = 0;
}

/***********************
* RetrieveRow: Retrieves the row that is asked for and checks that the row is completely valid
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kiRow: The Row number
* @parameter: _rfA: Reference to a float variable to store the A value of the Row
* @parameter: _rfB: Reference to a float variable to store the B value of the Row
* @parameter: _rfC: Reference to a float variable to store the C value of the Row
* @parameter: _rfD: Reference to a float variable to store the D value of the Row
* @return: bool: Successful or not
********************/
bool RetrieveRow(HWND _hDlg, const int _kiRow, float& _rfA, float& _rfB, float& _rfC, float& _rfD)
{
	// Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion for each Row Value
	wchar_t wstrTempA[100];
	wchar_t wstrTempB[100]; 
	wchar_t wstrTempC[100]; 
	wchar_t wstrTempD[100]; 

	// Retrieve the Row
	switch(_kiRow)
	{
	case(3):
		{
			GetDlgItemText( _hDlg, IDC_ROW3_A, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_ROW3_B, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_ROW3_C, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_ROW3_D, wstrTempD, 100);
		}
		break;
	case(2):
		{
			GetDlgItemText( _hDlg, IDC_ROW2_A, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_ROW2_B, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_ROW2_C, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_ROW2_D, wstrTempD, 100);
		}
		break;
	case(1):	
		{
			GetDlgItemText( _hDlg, IDC_ROW1_A, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_ROW1_B, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_ROW1_C, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_ROW1_D, wstrTempD, 100);
		}
		break;
	default:	// Message Box error
		{
			MessageBox(_hDlg, L"ERROR - Row Selection is invalid", L"Error", MB_ICONERROR | MB_OK);
			return false;
		}
	} // End Switch

	// Check all Row Values contain floats
	if(		ValidateFloat(wstrTempA)
		&&	ValidateFloat(wstrTempB)
		&&	ValidateFloat(wstrTempC)
		&&	ValidateFloat(wstrTempD) )
	{
		_rfA = WideStringToFloat(wstrTempA);			
		_rfB = WideStringToFloat(wstrTempB);			
		_rfC = WideStringToFloat(wstrTempC);
		_rfD = WideStringToFloat(wstrTempD);

		// Check against last column having a non-zero number and all zeros in the variable slots
		if( _rfD != 0)
		{
			if( (_rfA == 0) && (_rfB == 0) && (_rfC == 0))
			{
				MessageBox( _hDlg, L"ERROR - One of your equations is incorrect. Final column cannot contain non-zero number with all other row values being zero", L"Error", MB_OK);
				return false;
			}
		}

		return true;
	}
	else	// Brings up a Message Box Error
	{
		MessageBox( _hDlg, L"ERROR - One or more of your Row Values is not a number", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}	
}

/***********************
* SetRow: Sets The input Row to the input values
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kiRow: The Row number
* @parameter: _rfA: Reference to a float variable to set the A value of the Row
* @parameter: _rfB: Reference to a float variable to set the B value of the Row
* @parameter: _rfC: Reference to a float variable to set the C value of the Row
* @parameter: _rfD: Reference to a float variable to set the D value of the Row
* @return: void
********************/
void SetRow(HWND _hDlg, const int _kiRow, float& _rfA, float& _rfB, float& _rfC, float& _rfD)
{
	string strTemp; // Declare a temp string to use in storing values into the Edit Controls

	// The Row to Set
	switch(_kiRow)
	{
	case(3):
		{
			strTemp = FloatToString(_rfA);
			SetDlgItemTextA( _hDlg, IDC_ROW3_A,strTemp.c_str()); 
			strTemp = FloatToString(_rfB);
			SetDlgItemTextA( _hDlg, IDC_ROW3_B,strTemp.c_str()); 
			strTemp = FloatToString(_rfC);
			SetDlgItemTextA( _hDlg, IDC_ROW3_C,strTemp.c_str()); 
			strTemp = FloatToString(_rfD);
			SetDlgItemTextA( _hDlg, IDC_ROW3_D,strTemp.c_str()); 
		}
		break;
	case(2):
		{
			strTemp = FloatToString(_rfA);
			SetDlgItemTextA( _hDlg, IDC_ROW2_A,strTemp.c_str()); 
			strTemp = FloatToString(_rfB);
			SetDlgItemTextA( _hDlg, IDC_ROW2_B,strTemp.c_str()); 
			strTemp = FloatToString(_rfC);
			SetDlgItemTextA( _hDlg, IDC_ROW2_C,strTemp.c_str()); 
			strTemp = FloatToString(_rfD);
			SetDlgItemTextA( _hDlg, IDC_ROW2_D,strTemp.c_str()); 
		}
		break;
	case(1):	
		{
			strTemp = FloatToString(_rfA);
			SetDlgItemTextA( _hDlg, IDC_ROW1_A,strTemp.c_str()); 
			strTemp = FloatToString(_rfB);
			SetDlgItemTextA( _hDlg, IDC_ROW1_B,strTemp.c_str()); 
			strTemp = FloatToString(_rfC);
			SetDlgItemTextA( _hDlg, IDC_ROW1_C,strTemp.c_str()); 
			strTemp = FloatToString(_rfD);
			SetDlgItemTextA( _hDlg, IDC_ROW1_D,strTemp.c_str()); 
		}
		break;
	default:
		{
			MessageBox( _hDlg, L"ERROR - Programmers Error", L"Error", MB_ICONERROR | MB_OK);
		}
		
	} // End Switch
}

/***********************
* WideStringtoFloat: Converts a Wide Char String to a float
* @author: Callan Moore
* @parameter: _wstr: Constant Wide Char string to be converted
* @return: float: Input LPTSTR as a float variable
********************/
float WideStringToFloat(const wchar_t* _kwstr)
{
	// Take the size of the Wide Char String with one extra for null terminating char
	size_t stringLength = wcslen(_kwstr) + 1;
	size_t convertedChars = 0;

	if( stringLength == 1) // String is empty
	{
		return (0);
	}

	// Create new string with twice as many bytes for protection
	char* str = new char[stringLength*2];
	
	// Convert the Wide Char into Multibyte string
	wcstombs_s(&convertedChars, str, stringLength, _kwstr, _TRUNCATE);

	// Return the Float conversion of the string
	float fNum = stof(str);
	delete[] str;
	return (fNum);
}

/***********************
* WideStringtoInt: Converts a Wide Char String to a int
* @author: Callan Moore
* @parameter: _wstr: Constant Wide Char string to be converted
* @return: int: Input LPTSTR as a int variable
********************/
int WideStringToInt(const wchar_t* _kwstr)
{
	// Take the size of the Wide Char String with one extra for null terminating char
	size_t stringLength = wcslen(_kwstr) + 1;
	size_t convertedChars = 0;

	if( stringLength == 1) // String is empty
	{
		return (0);
	}

	// Create new string with twice as many bytes for protection
	char* str = new char[stringLength*2];
	
	// Convert the Wide Char into Multibyte string
	wcstombs_s(&convertedChars, str, stringLength, _kwstr, _TRUNCATE);

	// Return the Float conversion of the string
	int iNum = stoi(str);
	delete[] str;
	return (iNum);
}

/***********************
* FloatToString: Converts a float to a string
* @author: Callan Moore
* @parameter: _kfValue: Constant float variable to be converted
* @return: string: Input float as a string variable
********************/
string FloatToString(const float _kfValue)
{
	// Create string stream and write the float into it
	stringstream strStream;
	strStream << _kfValue;

	// Take the string from the stream and store it
	string strConverted = strStream.str();

	// Return the string
	return strConverted;
}

/***********************
* ValidateFloat: Checks if the input string can be converted to a float with no errors
* @author: Callan Moore
* @parameter: _wstr: The Wide Char String to validate
* @return: bool: Whether the input string can become a float
********************/
bool ValidateFloat(wchar_t* _wstr)
{
	// Take the size of the Wide Char String with one extra for null terminating char
	size_t stringLength = wcslen(_wstr) + 1;
	size_t convertedChars = 0;

	// Create new string with twice as many bytes for protection
	char* str = new char[stringLength*2];
	
	// Convert the Wide Char into Multibyte string
	wcstombs_s(&convertedChars, str, stringLength, _wstr, _TRUNCATE);

	istringstream iss(str);

    float fFloat;

	// Using noskipws, concatenate iss into fFloat
    iss >> noskipws >> fFloat; 
	
	// Check no flags were raised to say this is not a float
	if(iss.eof() && !iss.fail())
	{
		delete[] str;
		return (true);
	}
	else
	{
		delete[] str;
		return (false);
	}
}

/***********************
* ValidateInt: Checks if the input string can be converted to a int with no errors
* @author: Callan Moore
* @parameter: _wstr: The Wide Char String to validate
* @return: bool: Whether the input string can become a int
********************/
bool ValidateInt(wchar_t* _wstr)
{
	// Take the size of the Wide Char String with one extra for null terminating char
	size_t stringLength = wcslen(_wstr) + 1;
	size_t convertedChars = 0;

	// Create new string with twice as many bytes for protection
	char* str = new char[stringLength*2];
	
	// Convert the Wide Char into Multibyte string
	wcstombs_s(&convertedChars, str, stringLength, _wstr, _TRUNCATE);

	int iStrLength = strlen(str);

	for( int i = 0; i < iStrLength; i++)
	{
		if( i == 0)
		{
			if( !((str[i] == '-') || (isdigit(str[i]))))
			{
				return false;
			}
		}
		else if( !isdigit(str[i]))
		{
			return false;
		}
	}
	delete[] str;
	return true;
}