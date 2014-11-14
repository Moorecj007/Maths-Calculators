/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.cpp 
* Description : SLERP calculation function implementation
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
	SetDlgItemTextA( _hDlg, IDC_AI, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_AJ, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_AK, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_AC, strDefault.c_str());

	// Sets Row B Edit Controls to default value
	SetDlgItemTextA( _hDlg, IDC_BI, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_BJ, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_BK, strDefault.c_str());
	SetDlgItemTextA( _hDlg, IDC_BC, strDefault.c_str());

	// Sets the t Value to default value
	SetDlgItemTextA( _hDlg, IDC_T, strDefault.c_str());

	// Sets Resultant Row Edit Controls to empty
	SetDlgItemTextA( _hDlg, IDC_SLERPI, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_SLERPJ, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_SLERPK, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_SLERPC, strEmpty.c_str());

	// Sets the Resultant Matrix Edit Controls to Empty
	SetDlgItemTextA( _hDlg, IDC_MATRIX_11, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_12, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_13, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_14, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_21, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_22, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_23, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_24, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_31, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_32, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_33, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_34, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_41, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_42, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_43, strEmpty.c_str());
	SetDlgItemTextA( _hDlg, IDC_MATRIX_44, strEmpty.c_str());
}

/***********************
* SLERP: Calculates the SLERP Quaternion from two Quarternions and a t value
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void SLERP(HWND _hDlg)
{
	// Get the t Value from the Dialog Box
	wchar_t wstrTemp[100]; // Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion
	// Retrieve selected row
	GetDlgItemText( _hDlg, IDC_T, wstrTemp, 100);
	if( !ValidateFloat( wstrTemp))
	{
		MessageBox( _hDlg, L"ERROR - T Value is invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	float fT = WideStringToFloat(wstrTemp);

	// Declare float variables to store Quaternions values
	float fRow1I, fRow1J, fRow1K, fRow1C;
	float fRow2I, fRow2J, fRow2K, fRow2C;
	float fSlerpI, fSlerpJ, fSlerpK, fSlerpC;
	// Float variables to store calculation results
	float fOmega, fSinOmega, fCosOmega, fRow1Scalar, fRow2Scalar;

	if(	RetrieveRow( _hDlg, 'a', fRow1I, fRow1J, fRow1K, fRow1C)
		&& RetrieveRow( _hDlg, 'b', fRow2I, fRow2J, fRow2K, fRow2C) )
	{
		// Use Dot Product to compute the Cosine Angle for the two Quaternions
		fCosOmega = (fRow1I * fRow2I) + (fRow1J * fRow2J) + (fRow1K * fRow2K) + (fRow1C * fRow2C);

		// Dot Product is negative then Negate the second Quaternions to attain the shorter arc
		if( fCosOmega < 0)
		{
			fRow2I = (-fRow2I);
			fRow2J = (-fRow2J);
			fRow2K = (-fRow2K);
			fRow2C = (-fRow2C);
		}
		// If the gap between the Quaternions is too small use LERP instead to prevent divide by zero
		if( (1 - fCosOmega) < 0.0001f)
		{
			fRow1Scalar = 1 - fT;
			fRow2Scalar = fT;
		}
		// Use SLERP
		else
		{
			// Calculate the Sin(Omega) value using Trig Identity sin(sq)Omega + cos(sq)Omega = 1
			fSinOmega = sqrt( 1 - pow(fCosOmega, 2));

			// Compute the Omega (angle) by using the cosine and sine of it
			fOmega = atan2(fSinOmega, fCosOmega);
		
			// Calculate the two Quaternion Scalars
			fRow1Scalar = (sin(( 1 - fT) * fOmega) / fSinOmega);
			fRow2Scalar = (sin( fT* fOmega) / fSinOmega);
		}
		// Calculate the Slerp values
		fSlerpI = ( fRow1Scalar * fRow1I) + ( fRow2Scalar * fRow2I);
		fSlerpJ = ( fRow1Scalar * fRow1J) + ( fRow2Scalar * fRow2J);
		fSlerpK = ( fRow1Scalar * fRow1K) + ( fRow2Scalar * fRow2K);
		fSlerpC = ( fRow1Scalar * fRow1C) + ( fRow2Scalar * fRow2C);

		SetRow( _hDlg, fSlerpI, fSlerpJ, fSlerpK, fSlerpC);
	}
}

/***********************
* ConvertToMatrix: Takes in the Quaternions values and converts it into a matrix format
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcRow: The Row letter
* @return: void
********************/
void ConvertToMatrix( HWND _hDlg, const char _kcRow)
{
	// Floats to hold the passed in Quaternions Values
	float fI, fJ, fK, fC;

	// Temporary Variables for each matrix slot calculation
	float fCurrent;
	string strCurrent;

	if( RetrieveRow( _hDlg, _kcRow, fI, fJ, fK, fC))
	{
		// First Row of the Matrix
		fCurrent = 1 - (2 * pow(fJ, 2)) - (2 * pow(fK, 2));
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_11,strCurrent.c_str()); 
		fCurrent = ( 2 * fI * fJ) + ( 2 * fC * fK);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_12,strCurrent.c_str()); 
		fCurrent = ( 2 * fI * fK) - ( 2 * fC * fJ);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_13,strCurrent.c_str()); 
		fCurrent = 0;
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_14,strCurrent.c_str()); 

		// Second Row of the Matrix
		fCurrent = ( 2 * fI * fJ) - ( 2 * fC * fK);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_21,strCurrent.c_str()); 
		fCurrent = 1 - (2 * pow(fI, 2)) - ( 2 * pow(fK, 2));
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_22,strCurrent.c_str()); 
		fCurrent = ( 2 * fJ * fK) + ( 2 * fC * fI);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_23,strCurrent.c_str()); 
		fCurrent = 0;
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_24,strCurrent.c_str()); 

		// Third Row of the Matrix
		fCurrent = ( 2 * fI * fK) + ( 2 * fC * fJ);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_31,strCurrent.c_str()); 
		fCurrent = ( 2 * fJ * fK) - ( 2 * fC * fI);
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_32,strCurrent.c_str()); 
		fCurrent = 1 - (2 * pow(fI, 2)) - ( 2 * pow(fJ, 2));
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_33,strCurrent.c_str()); 
		fCurrent = 0;
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_34,strCurrent.c_str()); 

		// Forth Row of the Matrix
		fCurrent = 0;
		strCurrent = FloatToString(fCurrent);

		SetDlgItemTextA( _hDlg, IDC_MATRIX_41,strCurrent.c_str()); 
		SetDlgItemTextA( _hDlg, IDC_MATRIX_42,strCurrent.c_str()); 
		SetDlgItemTextA( _hDlg, IDC_MATRIX_43,strCurrent.c_str()); 
		fCurrent = 1;
		strCurrent = FloatToString(fCurrent);
		SetDlgItemTextA( _hDlg, IDC_MATRIX_44,strCurrent.c_str()); 
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
			GetDlgItemText( _hDlg, IDC_AI, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_AJ, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_AK, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_AC, wstrTempD, 100);
		}
		break;
	case('b'):
		{
			GetDlgItemText( _hDlg, IDC_BI, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_BJ, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_BK, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_BC, wstrTempD, 100);
		}
		break;
	case('s'):
		{
			GetDlgItemText( _hDlg, IDC_SLERPI, wstrTempA, 100);
			GetDlgItemText( _hDlg, IDC_SLERPJ, wstrTempB, 100);
			GetDlgItemText( _hDlg, IDC_SLERPK, wstrTempC, 100);
			GetDlgItemText( _hDlg, IDC_SLERPC, wstrTempD, 100);
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
* @parameter: _rfA: Reference to a float variable to set the A value of the Slerp Row
* @parameter: _rfB: Reference to a float variable to set the B value of the Slerp Row
* @parameter: _rfC: Reference to a float variable to set the C value of the Slerp Row
* @parameter: _rfD: Reference to a float variable to set the D value of the Slerp Row
* @return: void
********************/
void SetRow(HWND _hDlg, float& _rfA, float& _rfB, float& _rfC, float& _rfD)
{
	string strTemp; // Declare a temp string to use in storing values into the Edit Controls

	strTemp = FloatToString(_rfA);
	SetDlgItemTextA( _hDlg, IDC_SLERPI,strTemp.c_str()); 
	strTemp = FloatToString(_rfB);
	SetDlgItemTextA( _hDlg, IDC_SLERPJ,strTemp.c_str()); 
	strTemp = FloatToString(_rfC);
	SetDlgItemTextA( _hDlg, IDC_SLERPK,strTemp.c_str()); 
	strTemp = FloatToString(_rfD);
	SetDlgItemTextA( _hDlg, IDC_SLERPC,strTemp.c_str()); 
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
	delete[] str;
	return true;
}
