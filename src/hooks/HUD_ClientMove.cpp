#include <pch.h>
#include <base.h>

void Base::Hooks::HUD_ClientMove(struct playermove_s* ppmove, qboolean server)
{
	return Data::m_hw->o_cl_funcs.pClientMove(ppmove, server);
}