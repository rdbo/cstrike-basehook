#include <pch.h>
#include <base.h>

int Base::Hooks::CL_IsThirdPerson(void)
{
	return ((HUD_CL_ISTHIRDPERSON_FUNC)Data::m_hw->v_cl_funcs->get_original(INDEX_CL_ISTHIRDPERSON))();
}