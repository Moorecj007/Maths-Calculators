/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.cpp 
* Description : Quarternion calculation function implementation
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
	
	// Sets Row A Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_Q_AI, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_AJ, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_AK, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_AC, strDefault.c_str());

	// Sets Row B Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_Q_BI, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_BJ, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_BK, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_BC, strDefault.c_str());

	// Sets the t Value to default value
	SetDlgItemTextA( _hDlg, IDC_Q_TVALUE, strDefault.c_str());

	// Sets Resultant Row Edit Controls to empty
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTI, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTJ, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTK, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTC, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_Q_SINGLERESULT, strEmpty.c_str());
}

/***********************
* AddAB: Adds the Quaternions A and B together and puts the result in the result quaternion
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void AddAB( HWND _hDlg)
{
	// Declare float variables to hold all values
	float fAI, fAJ, fAK, fAC;
	float fBI, fBJ, fBK, fBC;
	float fResultI, fResultJ, fResultK, fResultC;

	if(	RetrieveRow( _hDlg, 'a', fAI, fAJ, fAK, fAC)
		&& RetrieveRow( _hDlg, 'b', fBI, fBJ, fBK, fBC) )
	{
		fResultI = fAI + fBI;
		fResultJ = fAJ + fBJ;
		fResultK = fAK + fBK;
		fResultC = fAC + fBC;

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* Subtract: Subtracts the second quaternion from the first and puts the result in the result quaternion
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cRow1: First Quaternion to be subtracted from
* @parameter: _cRow2: Second Quaternion to subtract from the first
* @return: void
********************/
void Subtract( HWND _hDlg, char _cRow1, char _cRow2)
{
	// Declare float variables to hold all values
	float fRow1I, fRow1J, fRow1K, fRow1C;
	float fRow2I, fRow2J, fRow2K, fRow2C;
	float fResultI, fResultJ, fResultK, fResultC;

	if(	RetrieveRow( _hDlg, _cRow1, fRow1I, fRow1J, fRow1K, fRow1C)
		&& RetrieveRow( _hDlg, _cRow2, fRow2I, fRow2J, fRow2K, fRow2C) )
	{
		fResultI = fRow1I - fRow2I;
		fResultJ = fRow1J - fRow2J;
		fResultK = fRow1K - fRow2K;
		fResultC = fRow1C - fRow2C;

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* Multiply: Multiply Quaternions two Quaternions together in given order and puts the result in the result quaternion
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cRow1: First Quaternion to multiply
* @parameter: _cRow2: Second Quaternion to multiply
* @return: void
********************/
void Multiply( HWND _hDlg, char _cRow1, char _cRow2)
{
	// Declare float variables to hold all values
	float fRow1I, fRow1J, fRow1K, fRow1C;
	float fRow2I, fRow2J, fRow2K, fRow2C;
	float fResultI, fResultJ, fResultK, fResultC;

	if(	RetrieveRow( _hDlg, _cRow1, fRow1I, fRow1J, fRow1K, fRow1C)
		&& RetrieveRow( _hDlg, _cRow2, fRow2I, fRow2J, fRow2K, fRow2C) )
	{
		// Quaternion muliplication calculation
		fResultI = (fRow1I * fRow2C) + (fRow1J * fRow2K) + ((-1) * fRow1K * fRow2J) + (fRow1C * fRow2I);
		fResultJ = ((-1) * fRow1I * fRow2K) + (fRow1J* fRow2C) + (fRow1K * fRow2I) + (fRow1C * fRow2J);
		fResultK = ( fRow1I * fRow2J) + ((-1) * fRow1J * fRow2I) + (fRow1K * fRow2C) + (fRow1C * fRow2K);
		fResultC = ((-1) * fRow1I * fRow2I) + ((-1) * fRow1J * fRow2J) + ((-1) * fRow1K * fRow2K) + (fRow1C * fRow2C);

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* DotProduct: Calculates the Dot Product of the the two Quaternions
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void DotProduct( HWND _hDlg)
{
	// Declare float variables to hold all values
	float fAI, fAJ, fAK, fAC;
	float fBI, fBJ, fBK, fBC;
	float fResult;

	if(	RetrieveRow( _hDlg, 'a', fAI, fAJ, fAK, fAC)
		&& RetrieveRow( _hDlg, 'b', fBI, fBJ, fBK, fBC) )
	{
		// Dot Product Calculation
		fResult = (fAI * fBI) + (fAJ * fBJ) + (fAK * fBK) + (fAC * fBC);

		// Set the Single Result Edit Control to the resultant float
		string strTemp; // Declare a temp string to use in storing values into the Edit Controls
		strTemp = FloatToString(fResult);
		SetDlgItemTextA( _hDlg, IDC_Q_SINGLERESULT,strTemp.c_str()); 
	}
}

/***********************
* Magnitude: Calculates the Magnitude of given Quaternion char
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cQuaternion: The Quarternion char to calculate the magnitude of
* @parameter: _bShowResult: Place the result in the dialog boxes edit control
* @return: float: The Magnitude
********************/
float Magnitude( HWND _hDlg, char _cQuaternion, bool _bShowResult)
{
	// Declare float variables to hold all values
	float fI, fJ, fK, fC;
	float fResult = 0;

	if(	RetrieveRow( _hDlg, _cQuaternion, fI, fJ, fK, fC) )
	{
		// Magnitude Calculation
		fResult = sqrt((fI * fI) + (fJ * fJ) + (fK * fK) + (fC * fC));

		// Set the Single Result Edit Control to the resultant float
		string strTemp; // Declare a temp string to use in storing values into the Edit Controls
		strTemp = FloatToString(fResult);
		SetDlgItemTextA( _hDlg, IDC_Q_SINGLERESULT,strTemp.c_str()); 	
	}
	return fResult;
}

/***********************
* Conjugate: Calculates the Conjugate of the given Quaternion
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cQuaternion: The Quarternion char to calculate the conjugate of
* @return: void
********************/
void Conjugate( HWND _hDlg, char _cQuaternion)
{
	// Declare float variables to hold all values
	float fI, fJ, fK, fC;
	float fResultI, fResultJ, fResultK, fResultC;

	if(	RetrieveRow( _hDlg, _cQuaternion, fI, fJ, fK, fC) )
	{
		// Calculating the conjugate
		fResultI = (-1) * fI;
		fResultJ = (-1) * fJ;
		fResultK = (-1) * fK;
		fResultC = fC;

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* Scale: Scales the given Quaternnion by the T value
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cQuaternion: The Quarternion char to scale
* @return: void
********************/
void Scale( HWND _hDlg, char _cQuaternion)
{

	wchar_t wstrTemp[100]; // Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion

	// Retrieve selected row
	GetDlgItemText( _hDlg, IDC_Q_TVALUE, wstrTemp, 100);

	if( !ValidateFloat( wstrTemp))
	{
		MessageBox( _hDlg, L"ERROR - T Value is invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	float fT = WideStringToFloat(wstrTemp);

	// Declare float variables to hold all values
	float fI, fJ, fK, fC;

	float fResultI, fResultJ, fResultK, fResultC;

	if(	RetrieveRow( _hDlg, _cQuaternion, fI, fJ, fK, fC) )
	{
		// Calculating the conjugate
		fResultI = fI * fT;
		fResultJ = fJ * fT;
		fResultK = fK * fT;
		fResultC = fC * fT;

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* Inverse: Calculates the Inverse of the given Quaternion
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _cQuaternion: The Quarternion char to calculate the Inverse of
* @return: void
********************/
void Inverse( HWND _hDlg, char _cQuaternion)
{
	// Declare float variables to hold all values
	float fI, fJ, fK, fC;
	float fResultI, fResultJ, fResultK, fResultC;

	// Get the Magnitude
	float fMagnitude = Magnitude( _hDlg, _cQuaternion, false);

	if(	RetrieveRow( _hDlg, _cQuaternion, fI, fJ, fK, fC) )
	{
		// Calculating the conjugate divided by the Magnitude
		fResultI = ((-1) * fI) / fMagnitude;
		fResultJ = ((-1) * fJ) / fMagnitude;
		fResultK = ((-1) * fK) / fMagnitude;
		fResultC = fC / fMagnitude;

		SetRow( _hDlg, fResultI, fResultJ, fResultK, fResultC);
	}
}

/***********************
* RetrieveRow: Retrieves the row that is asked for and checks that the row is completely valid
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcRow: The Row letter
* @parameter: _rfA: Reference to a float variable to store the A value of the Row
* @parameter: _rfB: Reference to a float variable to store the B value of the Row
* @parameter: _rfC: Reference to a float variable to store the C value of the Row
* @parameter: _rfD: Reference to a float variable to store the D value of the Row
* @return: bool: Successful or not
********************/
bool RetrieveRow(HWND _hDlg, const char _kcRow, float& _rfA, float& _rfB, float& _rfC, float& _rfD)
{
	// Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion for each Row Value
	wchar_t wstrTempA[100];
	wchar_t wstrTempB[100]; 
	wchar_t wstrTempC[100]; 
	wchar_t wstrTempD[100]; 

	// Retrieve the Row
	switch(_kcRow)
	{
	case('a'):
		{
			GetDlgItemText( _hDlg, IDC_Q_AI, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_Q_AJ, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_Q_AK, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_Q_AC, wstrTempD, 100);
		}
		break;
	case('b'):
		{
			GetDlgItemText( _hDlg, IDC_Q_BI, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_Q_BJ, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_Q_BK, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_Q_BC, wstrTempD, 100);
		}
		break;
	default:	// Message Box error
		{
			MessageBox(_hDlg, L"ERROR - Row Selection is invalid", L"Error", MB_OK);
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

		return true;
	}
	else	// Brings up a Message Box Error
	{
		MessageBox( _hDlg, L"ERROR - One or more of your Quaternion values is not a number", L"Error", MB_OK);
		return false;
	}	
}

/***********************
* SetRow: Sets The Result Row to the input values
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _rfA: Reference to a float variable to set the A value of the Result Row
* @parameter: _rfB: Reference to a float variable to set the B value of the Result Row
* @parameter: _rfC: Reference to a float variable to set the C value of the Result Row
* @parameter: _rfD: Reference to a float variable to set the D value of the Result Row
* @return: void
********************/
void SetRow(HWND _hDlg, float& _rfA, float& _rfB, float& _rfC, float& _rfD)
{
	string strTemp; // Declare a temp string to use in storing values into the Edit Controls

	strTemp = FloatToString(_rfA);
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTI,strTemp.c_str()); 
	strTemp = FloatToString(_rfB);
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTJ,strTemp.c_str()); 
	strTemp = FloatToString(_rfC);
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTK,strTemp.c_str()); 
	strTemp = FloatToString(_rfD);
	SetDlgItemTextA( _hDlg, IDC_Q_RESULTC,strTemp.c_str()); 
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

	// Create new string with twice as many bytes for protection as a wide char may become two 
	// bytes when converted to multibytes
	char* str = new char[stringLength*2];
	
	// Convert the Wide Char into Multibyte string
	wcstombs_s(&convertedChars, str, stringLength, _kwstr, _TRUNCATE);

	// Return the Float conversion of the string
	return (stof(str));
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

	bool bFirstDecimal = false;
	int iStrLength = strlen(str);

	// Checks each character of the string
	for( int i = 0; i < iStrLength; i++)
	{
		if( i == 0)	// First char is allowed to be a '-' for negative numbers
		{
			if( !((str[i] == '-') || (isdigit(str[i]))))
			{
				return false;
			}
		}
		else if( !isdigit(str[i]))
		{
			// String can hold one decimal point
			if( (str[i] == '.') && (bFirstDecimal == false))
			{
				bFirstDecimal = true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}
