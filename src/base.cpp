#include <pch.h>
#include <base.h>

//Data
HMODULE           Base::Data::hModule      = (HMODULE)NULL;
HWND              Base::Data::hWindow      = (HWND)NULL;
mem::voidptr_t    Base::Data::pSwapBuffers = (mem::voidptr_t)NULL;
SwapBuffers_t     Base::Data::oSwapBuffers = (SwapBuffers_t)NULL;
WndProc_t         Base::Data::oWndProc     = (WndProc_t)NULL;
#if defined(MEM_86)
mem::size_t       Base::Data::szSwapBuffers = 6;
#elif defined(MEM_64)
mem::size_t       Base::Data::szSwapBuffers = 13;
#endif
UINT              Base::Data::WmKeys[0xFF];
bool              Base::Data::Detached   = false;
bool              Base::Data::ShowMenu   = true;
bool              Base::Data::InitImGui  = false;

cstrike::hw*      Base::Data::m_hw     = nullptr;
cstrike::client*  Base::Data::m_client = nullptr;


//Functions

bool Base::Init()
{
	Data::m_client = new cstrike::client();
	Data::m_hw     = new cstrike::hw();
	Hooks::Init();
	return true;
}

bool Base::Shutdown()
{
	Hooks::Shutdown();
	delete Data::m_hw;
	delete Data::m_client;
	return true;
}

bool Base::Detach()
{
	Base::Shutdown();
	CreateThread(nullptr, 0, ExitThread, Data::hModule, 0, nullptr);
	return true;
}