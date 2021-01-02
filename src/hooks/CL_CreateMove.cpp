#include <pch.h>
#include <base.h>

void Base::Hooks::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	return Data::m_hw->o_cl_funcs.pCL_CreateMove(frametime, cmd, active);
}