#pragma once
#ifndef GAME_H
#define GAME_H

#include <pch.h>
#define BASE_OFFSET(base, offset) (&((char*)base)[offset])
#define MODULE_OFFSET(offset) BASE_OFFSET(this->Module.base, offset)

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

	class hw : GameModule
	{
	public:
		cldll_func_t* cl_funcs = nullptr;
		cldll_func_t      o_cl_funcs = {};
		CGame* Game = nullptr;
		cl_enginefuncs_s* Engfuncs = nullptr;
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

		}


		void Update()
		{
			this->cl_funcs = (cldll_func_t*)MODULE_OFFSET(Offsets::pClFuncs);
			memcpy((void*)& this->o_cl_funcs, (void*)this->cl_funcs, sizeof(this->o_cl_funcs));

			this->Engfuncs = (cl_enginefuncs_s*)MODULE_OFFSET(Offsets::pEngFuncs);
			this->Game = (CGame*)MODULE_OFFSET(Offsets::pGame);
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
}

#endif
