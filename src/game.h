#pragma once
#ifndef GAME_H
#define GAME_H

#include <pch.h>
#define BASE_OFFSET(base, offset) (&((char*)base)[offset])
#define MODULE_OFFSET(offset) BASE_OFFSET(this->Module.base, offset)

#define INDEX_CL_CREATEMOVE    14
#define INDEX_CL_ISTHIRDPERSON 15

namespace cstrike
{
	namespace Offsets
	{
		const uintptr_t pClFuncs  = 0x122ED60;
		const uintptr_t pEngFuncs = 0x136260;
		const uintptr_t pGame     = 0x6C3A90;
	}

	class GameModule
	{
	public:
		bool IsValid = false;
		mem::module_t Module;

	public:
		GameModule()
		{

		}

		void Update()
		{

		}

	protected:
		bool Setup(std::string module_name)
		{
			this->Module = mem::in::get_module(module_name);
			return this->Module.is_valid();
		}
	};

	class client : public GameModule
	{
	public:
		
	public:
		client()
		{
			if (!this->Setup("client.dll"))
				return;

			this->Update();
			this->IsValid = true;
		}

		void Update()
		{

		}
	};

	class hw : GameModule
	{
	public:
		cldll_func_t*     cl_funcs   = nullptr;
		mem::vtable_t*    v_cl_funcs = nullptr;
		CGame*            Game       = nullptr;
		cl_enginefuncs_s* Engfuncs   = nullptr;
	public:
		hw()
		{
			if (!this->Setup("hw.dll"))
				return;

			this->Update();
			this->IsValid = true;
		}

		~hw()
		{
			if (v_cl_funcs)
				delete this->v_cl_funcs;
		}


		void Update()
		{
			this->cl_funcs = (cldll_func_t*)MODULE_OFFSET(Offsets::pClFuncs);
			this->v_cl_funcs = new mem::vtable_t((mem::voidptr_t*)this->cl_funcs);

			this->Engfuncs = (cl_enginefuncs_s*)MODULE_OFFSET(Offsets::pEngFuncs);

			this->Game = (CGame*)MODULE_OFFSET(Offsets::pGame);
		}
	};
}

#endif
