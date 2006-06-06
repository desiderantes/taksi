//
// guiConfig.h
//
#ifndef _INC_guiConfig
#define _INC_guiConfig
#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>
#include "../common/CWndGDI.h"
#include "../common/CWindow.h"
#include "../common/CWndToolTip.h"

struct CTaksiConfigCustom;

struct CGui : public CWindowChild
{
public:
	CGui();

	bool CreateGuiWindow( UINT nCmdShow );
	void UpdateButtonStates();
	void UpdateButtonToolTips();

	static void OnCommandHelpURL();

private:
	static ATOM RegisterClass();
	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	bool OnCommand( int id, int iNotify, HWND hControl );
	bool IsButtonValid( TAKSI_HOTKEY_TYPE eKey ) const;
	LRESULT UpdateButton( TAKSI_HOTKEY_TYPE eKey );

	static int GetVirtKeyName( TCHAR* pszName, int iLen, BYTE bVirtKey );
	static int GetHotKeyName( TCHAR* pszName, int iLen, TAKSI_HOTKEY_TYPE eHotKey );

public:
#define BTN_QTY TAKSI_HOTKEY_QTY
	CWndGDI m_Bitmap[BTN_QTY*2];
	CWndToolTip m_ToolTips;
};
extern CGui g_GUI;

struct CGuiConfig : public CWindowChild
{
	// The config dialog window.
public:
	CGuiConfig();
	static INT_PTR CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	void SetStatusText( const TCHAR* pszText );
	void OnChanges();

	CTaksiConfigCustom* Custom_FindSelect( int index ) const;
	void Custom_Init( CTaksiConfigCustom* pCfg );
	void Custom_Update();
	void Custom_Read();

	void UpdateProcStats( const CTaksiProcStats& stats, DWORD dwMask );
	bool UpdateVideoCodec( const CVideoCodec& codec );
	bool UpdateAudioDevices( int uDeviceId );
	bool UpdateAudioCodec( const CWaveFormat& codec );
	void UpdateSettings( const CTaksiConfig& config );

	void OnCommandRestore();
	void OnCommandSave();
	bool OnCommandCaptureBrowse();
	void OnCommandVideoCodecButton();
	void OnCommandAudioCodecButton();
	void OnCommandKeyChange( HWND hControl );
	void OnCommandCustomAddButton();
	void OnCommandCustomDeleteButton();
	void OnCommandCustomKillFocus();

	bool OnTimer( UINT idTimer );
	bool OnNotify( int id, NMHDR* pHead );
	bool OnCommand( int id, int iNotify, HWND hControl );
	bool OnHelp( LPHELPINFO pHelpInfo );
	bool OnInitDialog( HWND hWnd, LPARAM lParam );

	void UpdateGuiTabCur();
	void SetSaveState( bool bChanged );

protected:
	CTaksiConfigCustom* m_pCustomCur;
	bool m_bDataUpdating;

public:
	CWndToolTip m_ToolTips;

	int m_iTabCur;	// persist this.
	HWND m_hControlTab;
	HWND m_hWndTab[5]; // N tabs

#define GuiConfigControl(a,b,c) HWND m_hControl##a;
#include "GuiConfigControls.tbl"
#undef GuiConfigControl

};
extern CGuiConfig g_GUIConfig;

#endif