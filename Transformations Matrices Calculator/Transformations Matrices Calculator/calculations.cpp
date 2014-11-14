/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.cpp 
* Description : Transformations calculation function implementation
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
	
	vector<vector<float>*>* pZeroMatrix = CreateZeroMatrix(4);

	// Set all values in the matrix to the default value
	for( int i = 0; i < 4; i++)
	{
		for( int j = 0; j < 4; j++)
		{
			(*(*pZeroMatrix)[i])[j] = fDefault;
		}
	}

	// Set the input/ result matrices to all zeros
	SetMatrix( _hDlg, 'r', pZeroMatrix);
	SetMatrix( _hDlg, 'c', pZeroMatrix);

	// Set the input Trasfomation boxes to 0
	SetDlgItemTextA( _hDlg, IDC_SCALE_X ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_SCALE_Y ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_SCALE_Z ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_TRANSLATION_X ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_TRANSLATION_Y ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_TRANSLATION_Z ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_ROTATION_X ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_ROTATION_Y ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_ROTATION_Z ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_ROTATION_ANGLE ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_PROJECTION_X ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_PROJECTION_Y ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_PROJECTION_Z ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_PROJECTION_DISTANCE ,strDefault.c_str()); 


	// Delete allocated memory in Matrix
	DeleteMatrix(pZeroMatrix);
	pZeroMatrix = 0;
}

/***********************
* Scale: Scales the Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: constant char that denotes the Matrix you want to scale
* @return: void
********************/
void Scale( HWND _hDlg, const char _kcMatrixChar)
{
	// Get the Scalar Values from the Dialog Box
	wchar_t wstrTempX[100];
	wchar_t wstrTempY[100];
	wchar_t wstrTempZ[100];
	GetDlgItemText( _hDlg, IDC_SCALE_X, wstrTempX, 100);
	GetDlgItemText( _hDlg, IDC_SCALE_Y, wstrTempY, 100);
	GetDlgItemText( _hDlg, IDC_SCALE_Z, wstrTempZ, 100);

	// Validate that the Matrix scalars are floats
	if(		!ValidateFloat( wstrTempX)
		||	!ValidateFloat( wstrTempY)
		||	!ValidateFloat( wstrTempZ) )
	{
		if( _kcMatrixChar == 'c')
		{
			MessageBox( _hDlg, L"ERROR - COLUMN Major Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
		}
		else
		{
			MessageBox( _hDlg, L"ERROR - ROW Major Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
		}
		return;
	}
	float fScalar = WideStringToFloat(wstrTempX);

	// Create a Blank Matrices
	vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);
	vector<vector<float>*>* pResultMatrix;

	if( RetrieveMatrix( _hDlg, _kcMatrixChar, pMatrix))
	{
		// Transpose Row Major Matrix into Column
		if( _kcMatrixChar == 'r')
		{
			Transpose(pMatrix);
		}

		// Create a scaling matrix starting with an identity Matrix
		vector<vector<float>*>* pScalarMatrix = CreateZeroMatrix(4);
		MakeIdentity( pScalarMatrix);

		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				if( iRow == iColumn)
				{
					if( iRow == 3)
					{
						// Homogenising is already done with Identity Matrix
						continue;
					}
					else
					{
						// Set the Diagonal to the Scalar Value
						(*(*pScalarMatrix)[iRow])[iColumn] = fScalar;
					}
				}
				else
				{
					// Set all other values to zero
					(*(*pScalarMatrix)[iRow])[iColumn] = 0;
				}
			}
		}

		// Multiply the Scalar matrix by the column Matrix
		pResultMatrix = Multiply( pScalarMatrix, pMatrix);

		// Transpose back into Row Major
		if( _kcMatrixChar == 'r')
		{
			Transpose(pResultMatrix);
		}

		SetMatrix( _hDlg, _kcMatrixChar, pResultMatrix);

		// Delete Allocated Matrix memory
		DeleteMatrix(pScalarMatrix);
		DeleteMatrix(pResultMatrix);
	}

	// Delete Allocated Matrix memory
	DeleteMatrix(pMatrix);

}

/***********************
* Skew: Skews the Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: constant char that denotes the Matrix you want to skew
* @return: void
********************/
void Skew( HWND _hDlg, const char _kcMatrixChar)
{
	// Get the Scalar Values from the Dialog Box
	wchar_t wstrTempX[100];
	wchar_t wstrTempY[100];
	wchar_t wstrTempZ[100];
	GetDlgItemText( _hDlg, IDC_SCALE_X, wstrTempX, 100);
	GetDlgItemText( _hDlg, IDC_SCALE_Y, wstrTempY, 100);
	GetDlgItemText( _hDlg, IDC_SCALE_Z, wstrTempZ, 100);

	// Validate that the Matrix scalars are floats
	if(		!ValidateFloat( wstrTempX)
		||	!ValidateFloat( wstrTempY)
		||	!ValidateFloat( wstrTempZ) )
	{
		if( _kcMatrixChar == 'c')
		{
			MessageBox( _hDlg, L"ERROR - One or more of your COLUMN Major Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
		}
		else
		{
			MessageBox( _hDlg, L"ERROR - One or more of your ROW Major Matrix Scalars are invalid", L"Error", MB_ICONERROR | MB_OK);
		}
		return;
		return;
	}
	float fScalarX = WideStringToFloat(wstrTempX);
	float fScalarY = WideStringToFloat(wstrTempY);
	float fScalarZ = WideStringToFloat(wstrTempZ);

	// Create a Blank Matrices
	vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);
	vector<vector<float>*>* pResultMatrix;

	if( RetrieveMatrix( _hDlg, _kcMatrixChar, pMatrix))
	{
		// Transpose Row Major Matrix into Column
		if( _kcMatrixChar == 'r')
		{
			Transpose(pMatrix);
		}

		// Create a scaling matrix starting with an identity Matrix
		vector<vector<float>*>* pSkewMatrix = CreateZeroMatrix(4);
		MakeIdentity( pSkewMatrix);

		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				if( iRow == iColumn)
				{
					if( iRow == 0)
					{
						(*(*pSkewMatrix)[iRow])[iColumn] = fScalarX;
					}
					else if( iRow == 1)
					{
						(*(*pSkewMatrix)[iRow])[iColumn] = fScalarY;
					}
					else if( iRow == 2)
					{
						(*(*pSkewMatrix)[iRow])[iColumn] = fScalarZ;
					}
					else
					{
						continue;
					}
				}
				else
				{
					// Set all other values to zero
					(*(*pSkewMatrix)[iRow])[iColumn] = 0;
				}
			}
		}

		// Multiply the Scalar matrix by the column Matrix
		pResultMatrix = Multiply( pSkewMatrix, pMatrix);

		// Transpose back into Row Major
		if( _kcMatrixChar == 'r')
		{
			Transpose(pResultMatrix);
		}

		SetMatrix( _hDlg, _kcMatrixChar, pResultMatrix);

		// Delete Allocated Matrix memory
		DeleteMatrix(pSkewMatrix);
		DeleteMatrix(pResultMatrix);
	}

	// Delete Allocated Matrix memory
	DeleteMatrix(pMatrix);
}

/***********************
* MakeIdentity: Makes an Identity Matrix and puts it in the input Matrix
* @author: Callan Moore
* @parameter: _pMatrix: Pointer to the Matrix to make an identity Matrix
* @return: void
********************/
void MakeIdentity( vector<vector<float>*>* _pMatrix)
{
	for( int iRow = 0; iRow < 4; iRow++)
	{
		for( int iColumn = 0; iColumn < 4; iColumn++)
		{
			// Diagonal needs to be set to one
			if( iRow == iColumn)
			{
				(*(*_pMatrix)[iRow])[iColumn] = 1;
			}
			else
			{
				(*(*_pMatrix)[iRow])[iColumn] = 0;
			}
		}
	}
}

/***********************
* MultiplyColumn: Multiplies the two matrices in Column Major Format
* @author: Callan Moore
* @parameter: pMatrix1: Left Matrix for the multiplication
* @parameter: pMatrix2: Right Matrix for the multiplication
* @return: vector<vector<float>*>*: Pointer to the Resultant Matrix
********************/
vector<vector<float>*>* Multiply( vector<vector<float>*>* pMatrix1, vector<vector<float>*>* pMatrix2)
{
	// Create Blank Matrix for the result
	vector<vector<float>*>* pMatrixResult = CreateZeroMatrix(4);

	float fCurrentCalculation;

	for( int iRow = 0; iRow < 4; iRow++)
	{
		for( int iColumn = 0; iColumn < 4; iColumn++)
		{
			fCurrentCalculation = 0; // Reset variable to zero each time

			// Repeat 4 times
			for( int i = 0; i < 4; i++)
			{
				// Go across the first column and down the second column multiplying and adding the result together
				fCurrentCalculation += (*(*pMatrix1)[iRow])[i] * (*(*pMatrix2)[i])[iColumn];
			}

			// Store the final result for each matrix entry
			(*(*pMatrixResult)[iRow])[iColumn] = fCurrentCalculation;
		}
	}

	// Delete the allocated memory for the matrices
	return (pMatrixResult);
}

/***********************
* Transpose: Transpose the given matrix
* @author: Callan Moore
* @parameter: _pfMatrix: Pointer to a Double vector of the Matrix to Transpose
* @return: void
********************/
void Transpose( vector<vector<float>*>* _pMatrix)
{
	// Create Blank Matrix
	vector<vector<float>*>* pTemp = CreateZeroMatrix(_pMatrix->size());

	// Transpose the matrix into a temporary Matrix
	for( unsigned int iRow = 0; iRow < _pMatrix->size(); iRow++)
	{
		for( unsigned int iColumn = 0; iColumn < _pMatrix->size(); iColumn++)
		{
			(*(*pTemp)[iRow])[iColumn] = (*(*_pMatrix)[iColumn])[iRow];
		}
	}

	// Assign each entry from the temp Matrix back into the original Matrix
	for( unsigned int iRow = 0; iRow < _pMatrix->size(); iRow++)
	{
		for( unsigned int iColumn = 0; iColumn < _pMatrix->size(); iColumn++)
		{
			(*(*_pMatrix)[iRow])[iColumn] = (*(*pTemp)[iRow])[iColumn];
		}
	}

	// Delete allocated memory to Temp Matrix
	DeleteMatrix(pTemp);
}

/***********************
* RetrieveMatrix: Retrieves the Matrix that corresponds with the input char
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: constant char that denotes the Matrix you want to retrieve
* @parameter: _pfMatrix: Pointer to a Double vector to store a matrix
* @return: bool: Successful or not
********************/
bool RetrieveMatrix( HWND _hDlg, const char _kcMatrixChar, vector<vector<float>*>* _pfMatrix)
{
	// Wide Strings to store the matrix values
	wchar_t wstrTemp11[100];
	wchar_t wstrTemp12[100];
	wchar_t wstrTemp13[100];
	wchar_t wstrTemp14[100];
	
	wchar_t wstrTemp21[100];
	wchar_t wstrTemp22[100];
	wchar_t wstrTemp23[100];
	wchar_t wstrTemp24[100];

	wchar_t wstrTemp31[100];
	wchar_t wstrTemp32[100];
	wchar_t wstrTemp33[100];
	wchar_t wstrTemp34[100];

	wchar_t wstrTemp41[100];
	wchar_t wstrTemp42[100];
	wchar_t wstrTemp43[100];
	wchar_t wstrTemp44[100];

	
	// Retrieve the text from the correct matrix
	switch( _kcMatrixChar)
	{
	case ('r'):
		{
			// Row 1 of the matrix
			GetDlgItemText( _hDlg, IDC_RM_11, wstrTemp11, 100);
			GetDlgItemText( _hDlg, IDC_RM_12, wstrTemp12, 100);
			GetDlgItemText( _hDlg, IDC_RM_13, wstrTemp13, 100);
			GetDlgItemText( _hDlg, IDC_RM_14, wstrTemp14, 100);

			// Row 2 of the matrix
			GetDlgItemText( _hDlg, IDC_RM_21, wstrTemp21, 100);
			GetDlgItemText( _hDlg, IDC_RM_22, wstrTemp22, 100);
			GetDlgItemText( _hDlg, IDC_RM_23, wstrTemp23, 100);
			GetDlgItemText( _hDlg, IDC_RM_24, wstrTemp24, 100);

			// Row 3 of the matrix
			GetDlgItemText( _hDlg, IDC_RM_31, wstrTemp31, 100);
			GetDlgItemText( _hDlg, IDC_RM_32, wstrTemp32, 100);
			GetDlgItemText( _hDlg, IDC_RM_33, wstrTemp33, 100);
			GetDlgItemText( _hDlg, IDC_RM_34, wstrTemp34, 100);

			// Row 4 of the matrix
			GetDlgItemText( _hDlg, IDC_RM_41, wstrTemp41, 100);
			GetDlgItemText( _hDlg, IDC_RM_42, wstrTemp42, 100);
			GetDlgItemText( _hDlg, IDC_RM_43, wstrTemp43, 100);
			GetDlgItemText( _hDlg, IDC_RM_44, wstrTemp44, 100);
		}
		break;
	case ('c'):
		{
			// Row 1 of the matrix
			GetDlgItemText( _hDlg, IDC_CM_11, wstrTemp11, 100);
			GetDlgItemText( _hDlg, IDC_CM_12, wstrTemp12, 100);
			GetDlgItemText( _hDlg, IDC_CM_13, wstrTemp13, 100);
			GetDlgItemText( _hDlg, IDC_CM_14, wstrTemp14, 100);

			// Row 2 of the matrix
			GetDlgItemText( _hDlg, IDC_CM_21, wstrTemp21, 100);
			GetDlgItemText( _hDlg, IDC_CM_22, wstrTemp22, 100);
			GetDlgItemText( _hDlg, IDC_CM_23, wstrTemp23, 100);
			GetDlgItemText( _hDlg, IDC_CM_24, wstrTemp24, 100);

			// Row 3 of the matrix
			GetDlgItemText( _hDlg, IDC_CM_31, wstrTemp31, 100);
			GetDlgItemText( _hDlg, IDC_CM_32, wstrTemp32, 100);
			GetDlgItemText( _hDlg, IDC_CM_33, wstrTemp33, 100);
			GetDlgItemText( _hDlg, IDC_CM_34, wstrTemp34, 100);

			// Row 4 of the matrix
			GetDlgItemText( _hDlg, IDC_CM_41, wstrTemp41, 100);
			GetDlgItemText( _hDlg, IDC_CM_42, wstrTemp42, 100);
			GetDlgItemText( _hDlg, IDC_CM_43, wstrTemp43, 100);
			GetDlgItemText( _hDlg, IDC_CM_44, wstrTemp44, 100);
		}
		break;
	default:
		{
			MessageBox(_hDlg, L"ERROR - Matrix Selection is invalid", L"Error", MB_OK);
			return false;
		}
		break;
	} // End Switch

	// Make sure that each Matrix value that was taken was a proper float value
	if(		ValidateFloat(wstrTemp11)
		&&	ValidateFloat(wstrTemp12)
		&&	ValidateFloat(wstrTemp13)
		&&	ValidateFloat(wstrTemp14)
		&&	ValidateFloat(wstrTemp21)
		&&	ValidateFloat(wstrTemp22)
		&&	ValidateFloat(wstrTemp23)
		&&	ValidateFloat(wstrTemp24)
		&&	ValidateFloat(wstrTemp31)
		&&	ValidateFloat(wstrTemp32)
		&&	ValidateFloat(wstrTemp33)
		&&	ValidateFloat(wstrTemp34)
		&&	ValidateFloat(wstrTemp41)
		&&	ValidateFloat(wstrTemp42)
		&&	ValidateFloat(wstrTemp43)
		&&	ValidateFloat(wstrTemp44) )
	{
		// Set all the Matrix values as floats into a double vector
		(*(*_pfMatrix)[0])[0] = WideStringToFloat(wstrTemp11);
		(*(*_pfMatrix)[0])[1] = WideStringToFloat(wstrTemp12);
		(*(*_pfMatrix)[0])[2] = WideStringToFloat(wstrTemp13);
		(*(*_pfMatrix)[0])[3] = WideStringToFloat(wstrTemp14);

		(*(*_pfMatrix)[1])[0] = WideStringToFloat(wstrTemp21);
		(*(*_pfMatrix)[1])[1] = WideStringToFloat(wstrTemp22);
		(*(*_pfMatrix)[1])[2] = WideStringToFloat(wstrTemp23);
		(*(*_pfMatrix)[1])[3] = WideStringToFloat(wstrTemp24);

		(*(*_pfMatrix)[2])[0] = WideStringToFloat(wstrTemp31);
		(*(*_pfMatrix)[2])[1] = WideStringToFloat(wstrTemp32);
		(*(*_pfMatrix)[2])[2] = WideStringToFloat(wstrTemp33);
		(*(*_pfMatrix)[2])[3] = WideStringToFloat(wstrTemp34);

		(*(*_pfMatrix)[3])[0] = WideStringToFloat(wstrTemp41);
		(*(*_pfMatrix)[3])[1] = WideStringToFloat(wstrTemp42);
		(*(*_pfMatrix)[3])[2] = WideStringToFloat(wstrTemp43);
		(*(*_pfMatrix)[3])[3] = WideStringToFloat(wstrTemp44);
	}
	else
	{
		if( _kcMatrixChar == 'c')
		{
			MessageBox( _hDlg, L"ERROR - One or more of your COLUMN major Matrix values is not a number", L"Error", MB_OK);
		}
		else
		{
			MessageBox( _hDlg, L"ERROR - One or more of your ROW Major Matrix values is not a number", L"Error", MB_OK);
		}
		return false;
	}

	return true;
}

/***********************
* SetMatrix: Sets a Matrix on the Dialog box to the values within the input Matrix (double vector)
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: constant char that denotes the Matrix you want to set
* @parameter: _pfMatrix: pointer to a Double vector to of the matrix that holds the values
* @return: void
********************/
void SetMatrix( HWND _hDlg, const char _kcMatrixChar, vector<vector<float>*>* _pfMatrix)
{
	// Declare strings for all the Matrix values
	string strTemp11 = FloatToString((*(*_pfMatrix)[0])[0]);
	string strTemp12 = FloatToString((*(*_pfMatrix)[0])[1]);
	string strTemp13 = FloatToString((*(*_pfMatrix)[0])[2]);
	string strTemp14 = FloatToString((*(*_pfMatrix)[0])[3]);

	string strTemp21 = FloatToString((*(*_pfMatrix)[1])[0]);
	string strTemp22 = FloatToString((*(*_pfMatrix)[1])[1]);
	string strTemp23 = FloatToString((*(*_pfMatrix)[1])[2]);
	string strTemp24 = FloatToString((*(*_pfMatrix)[1])[3]);

	string strTemp31 = FloatToString((*(*_pfMatrix)[2])[0]);
	string strTemp32 = FloatToString((*(*_pfMatrix)[2])[1]);
	string strTemp33 = FloatToString((*(*_pfMatrix)[2])[2]);
	string strTemp34 = FloatToString((*(*_pfMatrix)[2])[3]);

	string strTemp41 = FloatToString((*(*_pfMatrix)[3])[0]);
	string strTemp42 = FloatToString((*(*_pfMatrix)[3])[1]);
	string strTemp43 = FloatToString((*(*_pfMatrix)[3])[2]);
	string strTemp44 = FloatToString((*(*_pfMatrix)[3])[3]);

	switch( _kcMatrixChar)
	{
	case ('r'):
		{
			// Set Row 1 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_RM_11 ,strTemp11.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_12 ,strTemp12.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_13 ,strTemp13.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_14 ,strTemp14.c_str()); 

			// Set Row 2 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_RM_21 ,strTemp21.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_22 ,strTemp22.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_23 ,strTemp23.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_24 ,strTemp24.c_str()); 

			// Set Row 3 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_RM_31 ,strTemp31.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_32 ,strTemp32.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_33 ,strTemp33.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_34 ,strTemp34.c_str()); 

			// Set Row 4 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_RM_41 ,strTemp41.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_42 ,strTemp42.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_43 ,strTemp43.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_RM_44 ,strTemp44.c_str()); 
		}
		break;
	case ('c'):
		{
			// Set Row 1 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_CM_11 ,strTemp11.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_12 ,strTemp12.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_13 ,strTemp13.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_14 ,strTemp14.c_str()); 

			// Set Row 2 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_CM_21 ,strTemp21.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_22 ,strTemp22.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_23 ,strTemp23.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_24 ,strTemp24.c_str()); 

			// Set Row 3 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_CM_31 ,strTemp31.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_32 ,strTemp32.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_33 ,strTemp33.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_34 ,strTemp34.c_str()); 

			// Set Row 4 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_CM_41 ,strTemp41.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_42 ,strTemp42.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_43 ,strTemp43.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_CM_44 ,strTemp44.c_str()); 
		}
		break;
	
	default: break;
	} // End Swtich
}

/***********************
* CreateZeroMatrix: Creates a blank NxN matrix
* @author: Callan Moore
* @parameter: _iMatrixSize: The size of the matrix you wish to create
* @return: vector<vector<float>*>*: Pointer to a Blank NxN Matrix
********************/
vector<vector<float>*>* CreateZeroMatrix(int _iMatrixSize)
{
	vector<vector<float>*>* pfMatrix = new vector<vector<float>*>;

	// Creating the Rows
	for( int i = 0; i < _iMatrixSize; i++)
	{
		vector<float>* pVectTemp = new vector<float>;
		pfMatrix->push_back(pVectTemp);

		// Creating the Columns
		for( int j = 0; j < _iMatrixSize; j++)
		{
			(*pfMatrix)[i]->push_back(0);
		}
	}

	return pfMatrix;
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
