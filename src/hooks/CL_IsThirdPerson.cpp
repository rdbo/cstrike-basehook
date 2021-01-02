#include <pch.h>
#include <base.h>

int Base::Hooks::CL_IsThirdPerson(void)
{
	return Data::m_hw->o_cl_funcs.pCL_IsThirdPerson();
}