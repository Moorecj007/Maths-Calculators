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
	
	vector<vector<float>*>* pZeroMatrix = CreateZeroMatrix(4);

	// Set all values in the matrix to the default value
	for( int i = 0; i < 4; i++)
	{
		for( int j = 0; j < 4; j++)
		{
			(*(*pZeroMatrix)[i])[j] = fDefault;
		}
	}

	// Set the input matrices and the scalars to all zeros
	SetMatrix( _hDlg, 'a', pZeroMatrix);
	SetMatrix( _hDlg, 'b', pZeroMatrix);
	SetDlgItemTextA( _hDlg, IDC_M_AMULTIPLE ,strDefault.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_BMULTIPLE ,strDefault.c_str()); 

	// Set the resultant matrix to all empty
	SetDlgItemTextA( _hDlg, IDC_M_C11 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C12 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C13 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C14 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C21 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C22 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C23 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C24 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C31 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C32 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C33 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C34 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C41 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C42 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C43 ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_C44 ,strEmpty.c_str()); 

	// Set both the Determinant boxes to empty
	SetDlgItemTextA( _hDlg, IDC_M_ADETERMINANTNUM ,strEmpty.c_str()); 
	SetDlgItemTextA( _hDlg, IDC_M_BDETERMINANTNUM ,strEmpty.c_str()); 
	
	DeleteMatrix(pZeroMatrix);
	pZeroMatrix = 0;
}

/***********************
* MakeIdentity: Makes an Identity Matrix and puts it in the input Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: The corresponding char for the matrix you want to set
* @return: void
********************/
void MakeIdentity( HWND _hDlg, const char _kcMatrixChar)
{
	vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);

	for( int iRow = 0; iRow < 4; iRow++)
	{
		for( int iColumn = 0; iColumn < 4; iColumn++)
		{
			// Diagonal needs to be set to one
			if( iRow == iColumn)
			{
				(*(*pMatrix)[iRow])[iColumn] = 1;
			}
			else
			{
				(*(*pMatrix)[iRow])[iColumn] = 0;
			}
		}
	}
	SetMatrix( _hDlg, _kcMatrixChar, pMatrix);

	// delete allocated memory
	DeleteMatrix(pMatrix);
	pMatrix = 0;
}

/***********************
* Scale: Scales the corresponding Matrix by a scalar taken from dialog box
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: The corresponding char for the matrix you want to Multiply
* @return: void
********************/
void Scale( HWND _hDlg, const char _kcMatrixChar)
{
	// Get the Scalar Value from the Dialog Box
	wchar_t wstrTemp[100]; // Declare a temp Wide Char string to take LPTSTR from Edit Controls for conversion
	// Retrieve selected Multiple
	switch(_kcMatrixChar)
	{
	case ('a'):
		{
			GetDlgItemText( _hDlg, IDC_M_AMULTIPLE, wstrTemp, 100);
		}
		break;
	case ('b'):
		{
			GetDlgItemText( _hDlg, IDC_M_BMULTIPLE, wstrTemp, 100);
		}
		break;
	default: break;
	}// End Switch

	// Validate that the Matrix scalar is a float
	if( !ValidateFloat( wstrTemp))
	{
		MessageBox( _hDlg, L"ERROR - T Value is invalid", L"Error", MB_ICONERROR | MB_OK);
		return;
	}
	float fScalar = WideStringToFloat(wstrTemp);

	// Create a Matrix and retrieve the values from the Dialog Box
	vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);
	if( RetrieveMatrix( _hDlg, _kcMatrixChar, pMatrix))
	{
		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				(*(*pMatrix)[iRow])[iColumn] = ((*(*pMatrix)[iRow])[iColumn]) * fScalar;
			}
		}
		SetMatrix( _hDlg, _kcMatrixChar, pMatrix);
	}

	// Delete the allocated memory for the matrices
	DeleteMatrix(pMatrix);
}

/***********************
* Transpose: Transposes the Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: The corresponding char for the matrix you want to Multiply
* @return: void
********************/
void Transpose( HWND _hDlg, const char _kcMatrixChar)
{
	// Create a Matrix and retrieve the values from the Dialog Box
	vector<vector<float>*>* pNewMatrix = CreateZeroMatrix(4);
	vector<vector<float>*>* pOldMatrix = CreateZeroMatrix(4);

	if( RetrieveMatrix( _hDlg, _kcMatrixChar, pOldMatrix))
	{
		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				(*(*pNewMatrix)[iRow])[iColumn] = (*(*pOldMatrix)[iColumn])[iRow];
			}
		}
		SetMatrix( _hDlg, _kcMatrixChar, pNewMatrix);
	}

	// Delete the allocated memory for the matrices
	DeleteMatrix(pNewMatrix);
	DeleteMatrix(pOldMatrix);
}

/***********************
* Add: Adds Matrix A and B together storing the result in Resultant Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void Add( HWND _hDlg)
{
	// Create Blank Matrices
	vector<vector<float>*>* pMatrixA = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrixB = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrixResult = CreateZeroMatrix(4);

	if(		RetrieveMatrix( _hDlg, 'a', pMatrixA)
		 && RetrieveMatrix( _hDlg, 'b', pMatrixB) )
	{
		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				// Simple entry wise addition
				(*(*pMatrixResult)[iRow])[iColumn] = (*(*pMatrixA)[iRow])[iColumn] + (*(*pMatrixB)[iRow])[iColumn];
			}
		}

		SetMatrix( _hDlg, 'c', pMatrixResult);
	}

	// Delete the allocated memory for the matrices
	DeleteMatrix(pMatrixA);
	DeleteMatrix(pMatrixB);
	DeleteMatrix(pMatrixResult);
}

/***********************
* Subtract: Subtracts Matrix B from A storing the result in Resultant Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @return: void
********************/
void Subtract( HWND _hDlg)
{
	// Create Blank Matrices
	vector<vector<float>*>* pMatrixA = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrixB = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrixResult = CreateZeroMatrix(4);

	if(		RetrieveMatrix( _hDlg, 'a', pMatrixA)
		 && RetrieveMatrix( _hDlg, 'b', pMatrixB) )
	{
		for( int iRow = 0; iRow < 4; iRow++)
		{
			for( int iColumn = 0; iColumn < 4; iColumn++)
			{
				// Simple entry wise subtraction
				(*(*pMatrixResult)[iRow])[iColumn] = (*(*pMatrixA)[iRow])[iColumn] - (*(*pMatrixB)[iRow])[iColumn];
			}
		}

		SetMatrix( _hDlg, 'c', pMatrixResult);
	}

	// Delete the allocated memory for the matrices
	DeleteMatrix(pMatrixA);
	DeleteMatrix(pMatrixB);
	DeleteMatrix(pMatrixResult);
}

/***********************
* Multiply: Multiplies the two matrices in the input order using Column Major
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar1: Char corresponding to the first Matrix
* @parameter: _kcMatrixChar2: Char corresponding to the second Matrix
* @return: void
********************/
void Multiply( HWND _hDlg, const char _kcMatrixChar1, const char _kcMatrixChar2)
{
	// Create Blank Matrices
	vector<vector<float>*>* pMatrix1 = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrix2 = CreateZeroMatrix(4);
	vector<vector<float>*>* pMatrixResult = CreateZeroMatrix(4);

	float fCurrentCalculation;

	if(		RetrieveMatrix( _hDlg, _kcMatrixChar1, pMatrix1)
		 && RetrieveMatrix( _hDlg, _kcMatrixChar2, pMatrix2) )
	{
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

		SetMatrix( _hDlg, 'c', pMatrixResult);
	}

	// Delete the allocated memory for the matrices
	DeleteMatrix(pMatrix1);
	DeleteMatrix(pMatrix2);
	DeleteMatrix(pMatrixResult);
}

/***********************
* Determinant: Starting function for calculating the determinant of a matrix 
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: Char corresponding to the matrix you want the determinant of
* @return: float: The determinant of the matrix
********************/
float Determinant( HWND _hDlg, const char _kcMatrixChar)
{
	// Create Blank Matrix
	vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);
	float fDet = 0;

	if( RetrieveMatrix( _hDlg, _kcMatrixChar, pMatrix) )
	{
		fDet = Determinant(pMatrix, 4);
	}

	// Set the Edit Control to show the Determinant
	string strDet = FloatToString(fDet);
	switch(_kcMatrixChar)
	{
	case ('a'):
		{
			SetDlgItemTextA( _hDlg, IDC_M_ADETERMINANTNUM, strDet.c_str());
		}
		break;
	case ('b'):
		{
			SetDlgItemTextA( _hDlg, IDC_M_BDETERMINANTNUM, strDet.c_str());
		}
		break;
	default: break;
	} // End Switch

	// Delete the allocated memory for the matrices
	DeleteMatrix(pMatrix);

	return fDet;
}

/***********************
* Determinant: Rescursion part of calculating the determinant of a matrix
* @author: Callan Moore
* @parameter: _pMatrix: The matrix to find the determinant of
* @parameter: _iMatrixSize: The size of the matrix
* @return: float: The determinant of the input matrix
********************/
float Determinant( vector<vector<float>*>* _pMatrix, int _iMatrixSize)
{
	float fDet = 0;

	// Base case - Smallest derterminant calc is 2x2 matrix
	if( _iMatrixSize == 2)
	{
		fDet = ( (*(*_pMatrix)[0])[0] * (*(*_pMatrix)[1])[1] ) - ( (*(*_pMatrix)[1])[0] * (*(*_pMatrix)[0])[1] );
		return fDet;
	}
	// Breaking the matrix into smaller square matrices
	else
	{
		// Create a smaller square matrix
		vector<vector<float>*>* pSmallerMatrix = CreateZeroMatrix(_iMatrixSize - 1);
		int iSmallerRow, iSmallerColumn;
		
		for( int iScalar = 0; iScalar < _iMatrixSize; iScalar++)
		{
			iSmallerRow = 0;	// Reset Row count
			// Skipping top line as that is the scaler for the smaller matrix determinant
			for( int iRow = 1; iRow < _iMatrixSize; iRow++)
			{
				iSmallerColumn = 0;	// Reset Column count

				for( int iColumn = 0; iColumn < _iMatrixSize; iColumn++)
				{
					// Skipping the column that scalar is in
					if( iColumn == iScalar)
					{
						continue;
					}
					else
					{
						// Place the values into the smaller matrix ( without the scalars cross)
						(*(*pSmallerMatrix)[iSmallerRow])[iSmallerColumn] = (*(*_pMatrix)[iRow])[iColumn];
					}
					iSmallerColumn++;	// Increment the smaller column also
				}
				iSmallerRow++;			// Increment the smaller row also
			}
			
			// Multiply every second Scalar by negative 1 ( every second value needs to be subtracted)
			if( iScalar % 2 == 0)
			{
				// Multiply the Scalar by its determinant ( Recursion)
				fDet += (*(*_pMatrix)[0])[iScalar] * Determinant(pSmallerMatrix, _iMatrixSize - 1);
			}
			else
			{
				// Multiply the Scalar by its determinant ( Recursion)
				fDet += (-1) * (*(*_pMatrix)[0])[iScalar] * Determinant(pSmallerMatrix, _iMatrixSize - 1);
			}
		}
		// Delete the allocated memory for the matrices
		DeleteMatrix(pSmallerMatrix);
	}

	

	return fDet;
}

/***********************
* Inverse: Calculates the inverse if the Matrix
* @author: Callan Moore
* @parameter: _hDlg: Handle to the Dialog Box
* @parameter: _kcMatrixChar: Char corresponding to the matrix you want the Inverse of
* @return: void
********************/
void Inverse( HWND _hDlg, const char _kcMatrixChar)
{
	// Calculate the determinant
	float fDet = Determinant( _hDlg, _kcMatrixChar);
	int iScalarRow, iScalarColumn;

	// If determinant is 0 then the matrix is not invertible
	if( fDet != 0)
	{
		// Create Blank Matrix
		vector<vector<float>*>* pMatrix = CreateZeroMatrix(4);
		vector<vector<float>*>* pMatrixMinors = CreateZeroMatrix(4);
		vector<vector<float>*>* pMatrix3x3 = CreateZeroMatrix(3);
		vector<vector<float>*>* pMatrixAdjugate = CreateZeroMatrix(4);
		vector<vector<float>*>* pMatrixInverse = CreateZeroMatrix(4);
		vector<vector<float>*>* pMatrixCofactor;

		if( RetrieveMatrix( _hDlg, _kcMatrixChar, pMatrix))
		{
			iScalarRow = 0;	

			// Create Matrix of Minors ( Determinants of each matrix entry)
			for( int iRow = 0; iRow < 4; iRow++)
			{
				//iScalarColumn = 0;	// Reset Column count
				for( int iColumn = 0; iColumn < 4; iColumn++)
				{

					iScalarRow = 0;	// Reset Row count
						
					// Creates a 3x3 Matrix to calculate the determinant for the Matrix of Minors
					for( int iRow3x3 = 0; iRow3x3 < 4; iRow3x3++)
					{
						iScalarColumn = 0;	// Reset Column count

						// Skipping the Row that scalar is in
						if( iRow3x3 == iRow)
						{
							continue;
						}

						for( int iColumn3x3 = 0; iColumn3x3 < 4; iColumn3x3++)
						{
							// Skipping the column that scalar is in
							if( iColumn3x3 == iColumn)
							{
								continue;
							}
							else
							{
								// Place the values into the smaller matrix ( without the scalars cross)
								(*(*pMatrix3x3)[iScalarRow])[iScalarColumn] = (*(*pMatrix)[iRow3x3])[iColumn3x3];
							}
							iScalarColumn++;	// Increment the Scalar column also
						}
						iScalarRow++;			// Increment the Scalar row also
					}

					// Stores the determinant of each Matrix entry into the Matrix of Minors
					(*(*pMatrixMinors)[iRow])[iColumn] = Determinant( pMatrix3x3, 3);
				}
			}

			// Calculate the Cofactor Matrix of the Matrix of Minors
			pMatrixCofactor = Cofactor(pMatrixMinors);

			// Calculate the Adjugate Matrix from the Cofactor Matrix ( Transpose it)
			pMatrixAdjugate = Adjugate(pMatrixCofactor);

			// Divide each entry by the determinant to get the Inverse!
			for( int iRow = 0; iRow < 4; iRow++)
			{
				for( int iColumn = 0; iColumn < 4; iColumn++)
				{
					(*(*pMatrixInverse)[iRow])[iColumn] = (*(*pMatrixAdjugate)[iRow])[iColumn] / fDet;
				}
			}

			// Set the Matrix to its Inverse
			SetMatrix( _hDlg, _kcMatrixChar, pMatrixInverse);
		}

		// Delete the allocated memory for the matrices
		DeleteMatrix(pMatrix);
		DeleteMatrix(pMatrixMinors);
		DeleteMatrix(pMatrix3x3);
		DeleteMatrix(pMatrixCofactor);
		DeleteMatrix(pMatrixAdjugate);
		DeleteMatrix(pMatrixInverse);
	}
	else
	{
		MessageBox( _hDlg, L"Oops - Your Matrix is not invertible", L"OOPS", MB_ICONINFORMATION | MB_OK);
	}
}

/***********************
* Cofactor: Calculate the Cofactor of the input Matrix
* @author: Callan Moore
* @parameter: _pfMatrix: Pointer to a Double vector of the Matrix to cofactor
* @return: vector<vector<float>*>*: Pointer to a matrix that is the cofactor
********************/
vector<vector<float>*>* Cofactor( vector<vector<float>*>* _pMatrix)
{
	// Create Blank Matrix
	vector<vector<float>*>* pCofactor = CreateZeroMatrix(_pMatrix->size());

	for( unsigned int iRow = 0; iRow < pCofactor->size(); iRow++)
	{
		for( unsigned int iColumn = 0; iColumn < pCofactor->size(); iColumn++)
		{
			// If the row number plus column number is even (or the entry is 0) then do no change to the matrix entry
			if( (iRow + iColumn) % 2 == 0 || (*(*_pMatrix)[iRow])[iColumn] == 0)
			{
				(*(*pCofactor)[iRow])[iColumn] = (*(*_pMatrix)[iRow])[iColumn]; 
			}
			// If the row number plus column number is even then negate the entry
			else
			{
				(*(*pCofactor)[iRow])[iColumn] = (-1) * (*(*_pMatrix)[iRow])[iColumn]; 
			}
		}
	}

	return pCofactor;

	// Matrix memory allocation is deleted in Inverse function ( calling function)
}

/***********************
* Adjugate: Calculate the Adjugate of the input Matrix
* @author: Callan Moore
* @parameter: _pfMatrix: Pointer to a Double vector of the Matrix to Adjugate
* @return: vector<vector<float>*>*: Pointer to a matrix that is the Adjugate
********************/
vector<vector<float>*>* Adjugate( vector<vector<float>*>* _pMatrix)
{
	// Create Blank Matrix
	vector<vector<float>*>* pAdjugate = CreateZeroMatrix(_pMatrix->size());

	for( unsigned int iRow = 0; iRow < _pMatrix->size(); iRow++)
	{
		for( unsigned int iColumn = 0; iColumn < _pMatrix->size(); iColumn++)
		{
			(*(*pAdjugate)[iRow])[iColumn] = (*(*_pMatrix)[iColumn])[iRow];
		}
	}

	return pAdjugate;

	// Matrix memory allocation is deleted in Inverse function ( calling function)
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
	case ('a'):
		{
			// Row 1 of the matrix
			GetDlgItemText( _hDlg, IDC_M_A11, wstrTemp11, 100);
			GetDlgItemText( _hDlg, IDC_M_A12, wstrTemp12, 100);
			GetDlgItemText( _hDlg, IDC_M_A13, wstrTemp13, 100);
			GetDlgItemText( _hDlg, IDC_M_A14, wstrTemp14, 100);

			// Row 2 of the matrix
			GetDlgItemText( _hDlg, IDC_M_A21, wstrTemp21, 100);
			GetDlgItemText( _hDlg, IDC_M_A22, wstrTemp22, 100);
			GetDlgItemText( _hDlg, IDC_M_A23, wstrTemp23, 100);
			GetDlgItemText( _hDlg, IDC_M_A24, wstrTemp24, 100);

			// Row 3 of the matrix
			GetDlgItemText( _hDlg, IDC_M_A31, wstrTemp31, 100);
			GetDlgItemText( _hDlg, IDC_M_A32, wstrTemp32, 100);
			GetDlgItemText( _hDlg, IDC_M_A33, wstrTemp33, 100);
			GetDlgItemText( _hDlg, IDC_M_A34, wstrTemp34, 100);

			// Row 4 of the matrix
			GetDlgItemText( _hDlg, IDC_M_A41, wstrTemp41, 100);
			GetDlgItemText( _hDlg, IDC_M_A42, wstrTemp42, 100);
			GetDlgItemText( _hDlg, IDC_M_A43, wstrTemp43, 100);
			GetDlgItemText( _hDlg, IDC_M_A44, wstrTemp44, 100);
		}
		break;
	case ('b'):
		{
			// Row 1 of the matrix
			GetDlgItemText( _hDlg, IDC_M_B11, wstrTemp11, 100);
			GetDlgItemText( _hDlg, IDC_M_B12, wstrTemp12, 100);
			GetDlgItemText( _hDlg, IDC_M_B13, wstrTemp13, 100);
			GetDlgItemText( _hDlg, IDC_M_B14, wstrTemp14, 100);

			// Row 2 of the matrix
			GetDlgItemText( _hDlg, IDC_M_B21, wstrTemp21, 100);
			GetDlgItemText( _hDlg, IDC_M_B22, wstrTemp22, 100);
			GetDlgItemText( _hDlg, IDC_M_B23, wstrTemp23, 100);
			GetDlgItemText( _hDlg, IDC_M_B24, wstrTemp24, 100);

			// Row 3 of the matrix
			GetDlgItemText( _hDlg, IDC_M_B31, wstrTemp31, 100);
			GetDlgItemText( _hDlg, IDC_M_B32, wstrTemp32, 100);
			GetDlgItemText( _hDlg, IDC_M_B33, wstrTemp33, 100);
			GetDlgItemText( _hDlg, IDC_M_B34, wstrTemp34, 100);

			// Row 4 of the matrix
			GetDlgItemText( _hDlg, IDC_M_B41, wstrTemp41, 100);
			GetDlgItemText( _hDlg, IDC_M_B42, wstrTemp42, 100);
			GetDlgItemText( _hDlg, IDC_M_B43, wstrTemp43, 100);
			GetDlgItemText( _hDlg, IDC_M_B44, wstrTemp44, 100);
		}
		break;
	case ('c'):
		{
			// Row 1 of the matrix
			GetDlgItemText( _hDlg, IDC_M_C11, wstrTemp11, 100);
			GetDlgItemText( _hDlg, IDC_M_C12, wstrTemp12, 100);
			GetDlgItemText( _hDlg, IDC_M_C13, wstrTemp13, 100);
			GetDlgItemText( _hDlg, IDC_M_C14, wstrTemp14, 100);

			// Row 2 of the matrix
			GetDlgItemText( _hDlg, IDC_M_C21, wstrTemp21, 100);
			GetDlgItemText( _hDlg, IDC_M_C22, wstrTemp22, 100);
			GetDlgItemText( _hDlg, IDC_M_C23, wstrTemp23, 100);
			GetDlgItemText( _hDlg, IDC_M_C24, wstrTemp24, 100);

			// Row 3 of the matrix
			GetDlgItemText( _hDlg, IDC_M_C31, wstrTemp31, 100);
			GetDlgItemText( _hDlg, IDC_M_C32, wstrTemp32, 100);
			GetDlgItemText( _hDlg, IDC_M_C33, wstrTemp33, 100);
			GetDlgItemText( _hDlg, IDC_M_C34, wstrTemp34, 100);

			// Row 4 of the matrix
			GetDlgItemText( _hDlg, IDC_M_C41, wstrTemp41, 100);
			GetDlgItemText( _hDlg, IDC_M_C42, wstrTemp42, 100);
			GetDlgItemText( _hDlg, IDC_M_C43, wstrTemp43, 100);
			GetDlgItemText( _hDlg, IDC_M_C44, wstrTemp44, 100);
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
		MessageBox( _hDlg, L"ERROR - One or more of your Matrix values is not a number", L"Error", MB_OK);
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
	case ('a'):
		{
			// Set Row 1 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_A11 ,strTemp11.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A12 ,strTemp12.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A13 ,strTemp13.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A14 ,strTemp14.c_str()); 

			// Set Row 2 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_A21 ,strTemp21.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A22 ,strTemp22.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A23 ,strTemp23.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A24 ,strTemp24.c_str()); 

			// Set Row 3 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_A31 ,strTemp31.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A32 ,strTemp32.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A33 ,strTemp33.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A34 ,strTemp34.c_str()); 

			// Set Row 4 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_A41 ,strTemp41.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A42 ,strTemp42.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A43 ,strTemp43.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_A44 ,strTemp44.c_str()); 
		}
		break;
	case ('b'):
		{
			// Set Row 1 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_B11 ,strTemp11.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B12 ,strTemp12.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B13 ,strTemp13.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B14 ,strTemp14.c_str()); 

			// Set Row 2 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_B21 ,strTemp21.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B22 ,strTemp22.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B23 ,strTemp23.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B24 ,strTemp24.c_str()); 

			// Set Row 3 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_B31 ,strTemp31.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B32 ,strTemp32.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B33 ,strTemp33.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B34 ,strTemp34.c_str()); 

			// Set Row 4 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_B41 ,strTemp41.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B42 ,strTemp42.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B43 ,strTemp43.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_B44 ,strTemp44.c_str()); 
		}
		break;
	case ('c'):
		{
			// Set Row 1 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_C11 ,strTemp11.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C12 ,strTemp12.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C13 ,strTemp13.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C14 ,strTemp14.c_str()); 

			// Set Row 2 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_C21 ,strTemp21.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C22 ,strTemp22.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C23 ,strTemp23.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C24 ,strTemp24.c_str()); 

			// Set Row 3 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_C31 ,strTemp31.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C32 ,strTemp32.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C33 ,strTemp33.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C34 ,strTemp34.c_str()); 

			// Set Row 4 of the Matrix
			SetDlgItemTextA( _hDlg, IDC_M_C41 ,strTemp41.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C42 ,strTemp42.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C43 ,strTemp43.c_str()); 
			SetDlgItemTextA( _hDlg, IDC_M_C44 ,strTemp44.c_str()); 
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

		// Deleting the Columns
		while ( ((*_pMatrix).back())->empty() == false)
		{
			(*_pMatrix).back()->pop_back();
		}
		(*_pMatrix).pop_back();
	}
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
