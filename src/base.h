#pragma once
#ifndef BASE_H
#define BASE_H

#if defined(MEM_86)
#define WNDPROC_INDEX GWL_WNDPROC
#elif defined(MEM_64)
#define WNDPROC_INDEX GWLP_WNDPROC
#endif

#include "pch.h"
#include "game.h"

typedef BOOL(__stdcall* SwapBuffers_t)(_In_ HDC hdc);
typedef LRESULT(CALLBACK*  WndProc_t) (HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI MainThread(LPVOID lpThreadParameter);
DWORD WINAPI ExitThread(LPVOID lpThreadParameter);

namespace Base
{
	bool Init();
	bool Shutdown();
	bool Detach();

	namespace Data
	{
		extern HMODULE           hModule;
		extern HWND              hWindow;
		extern mem::voidptr_t    pSwapBuffers;
		extern SwapBuffers_t     oSwapBuffers;
		extern WndProc_t         oWndProc;
		extern mem::size_t       szSwapBuffers;
		extern UINT              WmKeys[0xFF];
		extern bool              Detached;
		extern bool              InitImGui;
		extern bool              ShowMenu;

		extern cstrike::hw*      m_hw;
		extern cstrike::client*  m_client;

		namespace Keys
		{
			const UINT ToggleMenu = VK_INSERT;
			const UINT DetachDll  = VK_END;
		}
	}

	namespace Hooks
	{
		bool Init();
		bool Shutdown();

		BOOL __stdcall SwapBuffers(_In_ HDC hdc);
		LRESULT CALLBACK  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void CL_CreateMove(float frametime, struct usercmd_s* cmd, int active);
		int  CL_IsThirdPerson(void);
		void HUD_ClientMove(struct playermove_s* ppmove, qboolean server);
	}
}

#endif