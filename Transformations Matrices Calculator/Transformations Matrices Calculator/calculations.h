/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.h 
* Description : Transformations calculation declaration file
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

// Library Includes
#include <iostream>
#include <vector>
#include <windows.h>		
#include <windowsx.h>		
#include <string>
#include <stdlib.h>
#include <sstream>

// Local Includes
#include "resource.h"
#include <math.h>

// Macros
//#define PI 3.1459265

using namespace std;

// Prototypes
void InitialSetup(HWND _hDlg);

vector<vector<float>*>* Scale( HWND _hDlg, const char _kcMatrixChar);
vector<vector<float>*>* Skew( HWND _hDlg, const char _kcMatrixChar);
vector<vector<float>*>* Translate( HWND _hDlg, const char _kcMatrixChar);
vector<vector<float>*>* Rotate( HWND _hDlg, const char _kcMatrixChar, int _iAxis);
vector<vector<float>*>* Project( HWND _hDlg, const char _kcMatrixChar, int _iAxis);

void MakeIdentity( vector<vector<float>*>* _pMatrix);
void Multiply( vector<vector<float>*>* pMatrix1, vector<vector<float>*>* pMatrix2);
void Transpose( vector<vector<float>*>* _pMatrix);
bool RetrieveMatrix( HWND _hDlg, const char _kcMatrixChar, vector<vector<float>*>* _pfMatrix);
void SetMatrix( HWND _hDlg, const char _kcMatrixChar, vector<vector<float>*>* _pfMatrix);
vector<vector<float>*>* CreateZeroMatrix(int _iMatrixSize);
void DeleteMatrix(vector<vector<float>*>* _pMatrix);
float WideStringToFloat(const wchar_t* _kwstr);
string FloatToString(const float _kfValue);
bool ValidateFloat(wchar_t* _wstr);