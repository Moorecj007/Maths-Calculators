/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : calculations.h 
* Description : Quarternion calculation declaration file
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

using namespace std;

// Prototypes
void InitialSetup(HWND _hDlg);

void SLERP(HWND _hDlg);
void ConvertToMatrix( HWND _hDlg,  const char _kcRow);

bool RetrieveRow(HWND _hDlg, const char _kcRow, float& _rfA, float& _rfB, float& _rfC, float& _rfD);
void SetRow(HWND _hDlg, float& _rfA, float& _rfB, float& _rfC, float& _rfD);
float WideStringToFloat(const wchar_t* _kwstr);
string FloatToString(const float _kfValue);
bool ValidateFloat(wchar_t* _wstr);