//
// CFileDirDlg.h
// Copyright 1992 - 2006 Dennis Robinson (www.menasoft.com)
//
#ifndef _INC_CFileDirDlg_H
#define _INC_CFileDirDlg_H
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFileDirDlg
{
	// Attach to the windows shell for the directories dialog.
public:
	CFileDirDlg( HWND hWndOwner, const TCHAR* pszDir );
	~CFileDirDlg();
	HRESULT DoModal( const TCHAR* pszPrompt );
	static bool __stdcall RemoveFileX( const TCHAR* pszPath, DWORD dwFlags ); // allow recursive delete.
	static HRESULT __stdcall CreateDirectoryX( const TCHAR* pszDir, HWND hWnd );
protected:
	static int CALLBACK BrowseCallbackProc( HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData );
public:
	TCHAR m_szDir[_MAX_PATH];	// in/out param
private:
	// Input Params.
	HWND m_hWndOwner;
	HWND m_hWnd;	// private use.
};

#endif