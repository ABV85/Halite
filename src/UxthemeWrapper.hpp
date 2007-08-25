
//         Copyright E�in O'Callaghan 2006 - 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "stdAfx.hpp"

namespace hal 
{

class uxthemeWrapper
{
public:
	typedef BOOL (WINAPI *ISAPPTHEMEDPROC)();
	typedef HRESULT (WINAPI *DRAWPARENTTHEMEBACKGROUND)(HWND, HDC, RECT*);
		
	uxthemeWrapper() :
		pIsAppThemed(0),
		pDrawThemeParentBackground(0)
	{			
		hinstDll = ::LoadLibrary(_T("UxTheme.dll"));
		if (hinstDll)
		{
			pIsAppThemed = 
			  (ISAPPTHEMEDPROC) ::GetProcAddress(hinstDll, "IsAppThemed");

			pDrawThemeParentBackground = 
			  (DRAWPARENTTHEMEBACKGROUND) ::GetProcAddress(hinstDll, "DrawThemeParentBackground");
			  
//			::MessageBox(0, (wformat(L"%1%, %2%") % pIsAppThemed % pDrawThemeParentBackground).str().c_str(), L"Result", 0);
		}
	}
	
	~uxthemeWrapper()
	{
		::FreeLibrary(hinstDll);
	}
	
	ISAPPTHEMEDPROC pIsAppThemed;
	DRAWPARENTTHEMEBACKGROUND pDrawThemeParentBackground;
	
private:
	HMODULE hinstDll;	
};

uxthemeWrapper& uxtheme();

};
