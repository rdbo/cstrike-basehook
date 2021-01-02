#include <pch.h>
#include <base.h>

static int init_createmove = false;

void Base::Hooks::CL_CreateMove(float frametime, struct usercmd_s* cmd, int active)
{
	return ((HUD_CL_CREATEMOVE_FUNC)Data::m_hw->v_cl_funcs->get_original(INDEX_CL_CREATEMOVE))(frametime, cmd, active);
}