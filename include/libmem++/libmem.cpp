/* libmem++ - C++ version of libmem
 * by rdbo
 * ---------------------------------
 * https://github.com/rdbo/libmem
 * ---------------------------------
 */

#include "libmem.hpp"

#if defined(MEM_COMPATIBLE)

//mem::process_t
mem::process_t::process_t()
{

}

mem::process_t::~process_t()
{
#	if defined(MEM_WIN)
	/*if (this->is_valid() && this->handle)
		CloseHandle(this->handle);*/
#	elif defined(MEM_LINUX)
#	endif
}

mem::bool_t mem::process_t::operator==(mem::process_t& process)
{
	return (bool_t)(
#		if defined(MEM_WIN)
		this->handle == process.handle &&
#		elif defined(MEM_LINUX)
#		endif
		this->name == process.name &&
		this->pid == process.pid
	);
}

mem::bool_t mem::process_t::is_valid()
{
	return (bool_t)(
#		if defined(MEM_WIN)
		this->handle != INVALID_HANDLE_VALUE &&
#		elif defined(MEM_LINUX)
#		endif
		this->name != MEM_STR("") &&
		this->pid  != (pid_t)-1
	);
}

//mem::module_t

mem::module_t::module_t()
{

}

mem::module_t::~module_t()
{
#	if defined(MEM_WIN)
	/*if (this->handle)
		CloseHandle(this->handle);*/
#	elif defined(MEM_LINUX)
#	endif
}

mem::bool_t mem::module_t::operator==(module_t& mod)
{
	return (bool_t)(
		this->name   == mod.name   &&
		this->path   == mod.path   &&
		this->base   == mod.base   &&
		this->end    == mod.end    &&
		this->size   == mod.size   &&
		this->handle == mod.handle
	);
}

mem::bool_t mem::module_t::is_valid()
{
	return (bool_t)(
		this->name != MEM_STR("") &&
		this->path != MEM_STR("") &&
		this->base != (voidptr_t)-1 &&
		this->end  != (voidptr_t)-1 &&
		this->size != (uintptr_t)-1 &&
		this->handle != (module_handle_t)-1
	);
}

//mem::page_t

mem::page_t::page_t()
{

}

mem::page_t::~page_t()
{

}

mem::bool_t mem::page_t::is_valid()
{
	return (bool_t)(
		base  != (voidptr_t)-1   &&
		size  != (uintptr_t)-1   &&
		end   != (voidptr_t)-1   &&
		flags != (flags_t)-1     &&
		protection != (prot_t)-1
	);
}

//mem::alloc_t

mem::alloc_t::alloc_t()
{
#	if defined(MEM_WIN)
	this->protection = PAGE_EXECUTE_READWRITE;
	this->type = MEM_COMMIT | MEM_RESERVE;
#	elif defined(MEM_LINUX)
	this->protection = PROT_EXEC | PROT_READ | PROT_WRITE;
	this->type = MAP_ANON | MAP_PRIVATE;
#	endif
}

mem::alloc_t::alloc_t(mem::prot_t prot)
{
#	if defined(MEM_WIN)
	this->protection = prot;
	this->type = MEM_COMMIT | MEM_RESERVE;
#	elif defined(MEM_LINUX)
	this->protection = prot;
	this->type = MAP_ANON | MAP_PRIVATE;
#	endif
}

mem::alloc_t::alloc_t(mem::prot_t prot, mem::alloc_type_t type)
{
	this->protection = prot;
	this->type = type;
}

mem::alloc_t::~alloc_t()
{

}

mem::bool_t mem::alloc_t::is_valid()
{
	return (bool_t)(
		this->protection != (prot_t)-1 &&
		this->type != (alloc_type_t)-1
	);
}

//mem::lib_t

mem::lib_t::lib_t()
{
#	if defined(MEM_WIN)
#	elif defined(MEM_LINUX)
	this->mode = RTLD_LAZY;
#	endif
}

mem::lib_t::lib_t(string_t path)
{
	this->path = path;
#	if defined(MEM_WIN)
#	elif defined(MEM_LINUX)
	this->mode = RTLD_LAZY;
#	endif
}

mem::lib_t::lib_t(string_t path, int_t mode)
{
	this->path = path;
#	if defined(MEM_WIN)
#	elif defined(MEM_LINUX)
	this->mode = mode;
#	endif
}

mem::bool_t mem::lib_t::is_valid()
{
	return (bool_t)(
		this->path != MEM_STR("")
	);
}

//mem::vtable_t

mem::vtable_t::vtable_t(voidptr_t* vtable)
{
	this->table = vtable;
}

mem::vtable_t::~vtable_t()
{

}

mem::bool_t mem::vtable_t::is_valid()
{
	return (bool_t)(
		this->table != (voidptr_t*)-1
	);
}

mem::voidptr_t mem::vtable_t::get_function(size_t index)
{
    return this->table[index];
}

mem::voidptr_t mem::vtable_t::get_original(size_t index)
{
    return this->orig_table.at(index);
}

mem::bool_t mem::vtable_t::hook(size_t index, voidptr_t dst)
{
	if (!this->is_valid()) return false;

#   if defined(MEM_WIN)
    prot_t prot = PAGE_EXECUTE_READWRITE;
#   elif defined(MEM_LINUX)
    prot_t prot = PROT_EXEC | PROT_READ | PROT_WRITE;
#   endif

    in::protect(&this->table[index], sizeof(voidptr_t), prot);

	this->orig_table.insert(std::pair<size_t, voidptr_t>(index, this->get_function(index)));
	this->table[index] = dst;
	return true;
}

mem::bool_t mem::vtable_t::restore(size_t index)
{
	if (!this->is_valid()) return false;

	for (auto i = this->orig_table.begin(); i != this->orig_table.end(); i++)
	{
		if (i->first == index)
		{
			this->table[index] = i->second;
			return true;
		}
	}

	return false;
}

mem::bool_t mem::vtable_t::restore_all()
{
	if (!this->is_valid()) return false;

	for (auto i = this->orig_table.begin(); i != this->orig_table.end(); i++)
		this->table[i->first] = i->second;

	return true;
}

//libmem

mem::string_t  mem::parse_mask(string_t mask)
{
	for (::size_t i = 0; i < mask.length(); i++)
	{
		if (mask[i] == MEM_STR('X'))
		{
			mask[i] = std::tolower(mask[i]);;
			break;
		}

		if (mask[i] != MEM_STR('x'))
		{
			mask[i] = MEM_STR('?');
			break;
		}
	}

	return mask;
}

mem::uintptr_t mem::get_page_size()
{
	uintptr_t page_size = (uintptr_t)MEM_BAD;
#	if defined(MEM_WIN)
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	page_size = (uintptr_t)si.dwPageSize;
#	elif defined(MEM_LINUX)
	page_size = (uintptr_t)sysconf(_SC_PAGE_SIZE);
#	endif

	return page_size;
}

//ex

mem::pid_t mem::ex::get_pid(string_t process_name)
{
	pid_t pid = (pid_t)MEM_BAD;
#	if defined(MEM_WIN)
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!MEM_STR_CMP(procEntry.szExeFile, process_name.c_str()))
				{
					pid = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
#	elif defined(MEM_LINUX)
	DIR* pdir = opendir("/proc");
	if (!pdir)
		return pid;

	struct dirent* pdirent = (struct dirent*)0;
	while (pid < 0 && (pdirent = readdir(pdir)))
	{
		pid_t id = atoi(pdirent->d_name);
		if (id > 0)
		{
			string_t proc_name = ex::get_process_name(id);
			if (process_name == proc_name)
			{
				pid = id;
				break;
			}
		}
	}
	closedir(pdir);
#	endif
	return pid;
}

mem::string_t mem::ex::get_process_name(pid_t pid)
{
	string_t process_name = MEM_STR("");
#	if defined(MEM_WIN)
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (pid == procEntry.th32ProcessID)
				{
					process_name = procEntry.szExeFile;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
#	elif defined(MEM_LINUX)
	char path[64];
	memset(path, 0x0, sizeof(path));
	snprintf(path, sizeof(path), "/proc/%i/exe", pid);

	char buffer[PATH_MAX];
	memset(buffer, 0x0, sizeof(buffer));
	readlink(path, buffer, sizeof(buffer));
	char* temp = buffer;
	char* proc_name = (char*)0;
	while ((temp = strstr(temp, "/")) && temp != (char*)-1)
	{
		proc_name = &temp[1];
		temp = proc_name;
	}

	if (!proc_name || proc_name == (char*)-1)
		return process_name;

	process_name = proc_name;
#	endif

	return process_name;
}

mem::process_t mem::ex::get_process(pid_t pid)
{
	process_t process = process_t();
	process.pid = pid;
	process.name = ex::get_process_name(process.pid);
#	if defined(MEM_WIN)
	process.handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process.pid);
#	elif defined(MEM_LINUX)
#	endif

	return process;
}

mem::process_t mem::ex::get_process(string_t process_name)
{
	process_t process = process_t();
	pid_t pid = ex::get_pid(process_name);
	if (pid != (pid_t)MEM_BAD)
		process = ex::get_process(pid);

	return process;
}

mem::process_list_t mem::ex::get_process_list()
{
	process_list_t proc_list = process_list_t();
#	if defined(MEM_WIN)
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				process_t process = ex::get_process(procEntry.th32ProcessID);
				if(process.is_valid())
					proc_list.push_back(process);
			} while (Process32Next(hSnap, &procEntry));

		}
	}
	CloseHandle(hSnap);
#	elif defined(MEM_LINUX)
	DIR* pdir = opendir("/proc");
	if (!pdir)
		return proc_list;

	struct dirent* pdirent = (struct dirent*)0;
	while ((pdirent = readdir(pdir)) && pdirent)
	{
		pid_t id = (pid_t)atoi(pdirent->d_name);
		if (id > 0)
		{
			process_t process = ex::get_process(id);
			if(process.is_valid())
				proc_list.push_back(process);
		}
	}
	closedir(pdir);
#	endif

	return proc_list;
}

mem::module_t mem::ex::get_module(process_t process, string_t module_name)
{
	module_t mod = module_t();
	if (!process.is_valid()) return mod;

#	if defined(MEM_WIN)
	MODULEENTRY32 module_info;
	module_info.dwSize = sizeof(MODULEENTRY32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process.pid);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!MEM_STR_CMP(modEntry.szModule, module_name.c_str()) || !MEM_STR_CMP(modEntry.szExePath, module_name.c_str()))
				{
					module_info = modEntry;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}

	CloseHandle(hSnap);

	mod.base = (voidptr_t)module_info.modBaseAddr;
	mod.size = (size_t)module_info.modBaseSize;
	mod.end  = (voidptr_t)((uintptr_t)mod.base + mod.size);
	mod.handle = (module_handle_t)module_info.hModule;
	mod.path = module_info.szExePath;
	mod.name = module_info.szModule;
#	elif defined(MEM_LINUX)
	std::stringstream maps_file;
	maps_file << "/proc/" << process.pid << "/maps";
	std::ifstream maps_fs(maps_file.str());
	if(!maps_fs.is_open()) return mod;
	maps_file.str(std::string());
	maps_file << maps_fs.rdbuf();

	//--

	size_t module_path_pos = 0;
	size_t module_path_end = 0;
	std::string module_path_str = "";

	module_path_pos = maps_file.str().find(module_name);
	size_t holder = module_path_pos;
    module_path_pos = maps_file.str().rfind('\n', module_path_pos);
    if(module_path_pos == maps_file.str().npos)
        module_path_pos = maps_file.str().rfind("              /", holder);
    module_path_pos = maps_file.str().find('/', module_path_pos);
    module_path_end = maps_file.str().find('\n', module_path_pos);
    if(module_path_pos == maps_file.str().npos || module_path_end == maps_file.str().npos) return mod;
    module_path_str = maps_file.str().substr(module_path_pos, module_path_end - module_path_pos);

    //--

    std::string module_name_str = module_path_str.substr(
        module_path_str.rfind('/') + 1
    );

    //--

    size_t base_address_pos = maps_file.str().rfind('\n', module_path_pos) + 1;
    size_t base_address_end = maps_file.str().find('-', base_address_pos);
    if(base_address_pos == maps_file.str().npos || base_address_end == maps_file.str().npos) return mod;
    std::string base_address_str = maps_file.str().substr(base_address_pos, base_address_end - base_address_pos);
    base_address_str += '\0';
    void* base_address = MEM_STR_TO_PTR(base_address_str.c_str());

    //--

    size_t end_address_pos = 0;
    size_t end_address_end = 0;
    std::string end_address_str = "";
    void* end_address = (void*)-1;

    end_address_pos = maps_file.str().rfind(module_path_str);
    end_address_pos = maps_file.str().rfind('\n', end_address_pos) + 1;
    end_address_pos = maps_file.str().find('-', end_address_pos) + 1;

    end_address_end = maps_file.str().find(' ', end_address_pos);

    if(end_address_pos == maps_file.str().npos || end_address_end == maps_file.str().npos) return mod;

    end_address_str = maps_file.str().substr(end_address_pos, end_address_end - end_address_pos);
    end_address_str += '\0';
    end_address = MEM_STR_TO_PTR(end_address_str.c_str());

    //--

    uintptr_t module_size = (uintptr_t)end_address - (uintptr_t)base_address;

    //--

    mod.name = string_t(module_name_str);
    mod.path = string_t(module_path_str);
    mod.base = base_address;
    mod.size = module_size;
    mod.end  = end_address;

    maps_fs.close();

#	endif

	return mod;
}

mem::module_list_t mem::ex::get_module_list(process_t process)
{
	module_list_t mod_list = module_list_t();
	if (!process.is_valid()) return mod_list;
#	if defined(MEM_WIN)
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process.pid);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				module_t mod = module_t();
				mod.base = (voidptr_t)modEntry.modBaseAddr;
				mod.size = (uintptr_t)modEntry.modBaseSize;
				mod.end =  (voidptr_t)((uintptr_t)mod.base + mod.size);
				mod.name = modEntry.szModule;
				mod.path = modEntry.szExePath;
				mod.handle = modEntry.hModule;

				mod_list.push_back(mod);
			} while (Module32Next(hSnap, &modEntry));
		}
	}

	CloseHandle(hSnap);
#	elif defined(MEM_LINUX)
	std::stringstream maps_file;
	maps_file << "/proc/" << process.pid << "/maps";
	std::ifstream maps_fs(maps_file.str());
	if(!maps_fs.is_open()) return mod_list;
	maps_file.str(std::string());
	maps_file << maps_fs.rdbuf();

	size_t module_path_pos = 0;
	size_t module_path_end = 0;
	size_t next = 0;

	while((module_path_pos = maps_file.str().find('/', next)) && module_path_pos != maps_file.str().npos)
	{
		module_path_end = maps_file.str().find('\n', module_path_pos);
		std::string module_path_str = maps_file.str().substr(module_path_pos, module_path_end - module_path_pos);

		size_t module_name_pos = maps_file.str().rfind('/', module_path_end) + 1;
		size_t module_name_end = module_path_end;
		std::string module_name_str = maps_file.str().substr(module_name_pos, module_name_end - module_name_pos);

		size_t base_address_pos = maps_file.str().rfind('\n', module_path_pos) + 1;
		size_t base_address_end = maps_file.str().find('-', base_address_pos);
		std::string base_address_str = maps_file.str().substr(base_address_pos, base_address_end - base_address_pos);
		base_address_str += '\0';
		voidptr_t base_address = MEM_STR_TO_PTR(base_address_str.c_str());

		size_t   end_address_pos = maps_file.str().rfind('\n', maps_file.str().rfind(module_path_str));
		end_address_pos = maps_file.str().find('-', end_address_pos) + 1;
		size_t   end_address_end = maps_file.str().find(' ', end_address_pos);
		std::string end_address_str = maps_file.str().substr(end_address_pos, end_address_end);
		end_address_str += '\0';
		voidptr_t end_address = MEM_STR_TO_PTR(end_address_str.c_str());

		size_t mod_size = (uintptr_t)end_address - (uintptr_t)base_address;

		module_handle_t handle = (module_handle_t)MEM_BAD;

		module_t mod = module_t();
		mod.name = string_t(module_name_str);
		mod.path = string_t(module_path_str);
		mod.base = base_address;
		mod.size = mod_size;
		mod.end  = end_address;
		mod.handle = handle;

		mod_list.push_back(mod);
		next = maps_file.str().find('\n', end_address_end);
		if(next == maps_file.str().npos) break;
	}

	maps_fs.close();
#	endif

	return mod_list;
}

mem::page_t mem::ex::get_page(process_t process, voidptr_t src)
{
	page_t page = page_t();
	if (!process.is_valid()) return page;
#	if defined(MEM_WIN)
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQueryEx(process.handle, src, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
	page.base  = mbi.BaseAddress;
	page.size  = mbi.RegionSize;
	page.end   = (voidptr_t)((uintptr_t)page.base + page.size);
	page.protection = mbi.Protect;
	page.flags = mbi.Type;
#	elif defined(MEM_LINUX)
	std::stringstream maps_file;
	maps_file << "/proc/" << process.pid << "/maps";
	std::ifstream maps_fs(maps_file.str());
	if(!maps_fs.is_open()) return page;
	maps_file.str(std::string());
	maps_file << maps_fs.rdbuf();

	std::stringstream src_str;
	src_str << src;

	size_t to_remove = src_str.str().find("0x");

	if(to_remove != src_str.str().npos)
		src_str.str(src_str.str().erase(to_remove, strlen("0x")));

	size_t page_base_pos = maps_file.str().rfind(src_str.str());
	if(page_base_pos == maps_file.str().npos) return page;

	size_t page_end_pos = maps_file.str().find('-') + 1;
	size_t page_end_end = maps_file.str().find(' ');
	std::string page_end_str = maps_file.str().substr(page_end_pos, page_end_end - page_end_pos);
	voidptr_t page_end = MEM_STR_TO_PTR(page_end_str.c_str());

	size_t start = maps_file.str().find(' ', page_base_pos) + 1;
	size_t end = start + 4;

	page.protection = 0;

	for(size_t i = start; i < end; i++)
	{
		char c = maps_file.str()[i];
		switch(c)
		{
			case 'r':
			page.protection |= PROT_READ;
			break;

			case 'w':
			page.protection |= PROT_WRITE;
			break;

			case 'x':
			page.protection |= PROT_EXEC;
			break;

			case 'p':
			page.flags = MAP_PRIVATE;
			break;

			case 's':
			page.flags = MAP_SHARED;
			break;

			default:
			break;
		}
	}

	page.base = src;
	page.size = (uintptr_t)page_end - (uintptr_t)src;
	page.end  = page_end;


	maps_fs.close();
#	endif

	return page;
}

mem::bool_t mem::ex::is_process_running(process_t process)
{
	bool_t ret = MEM_FALSE;
	if (!process.is_valid()) return ret;
#   if defined(MEM_WIN)
	DWORD exit_code;
	GetExitCodeProcess(process.handle, &exit_code);
	ret = (bool_t)(exit_code == STILL_ACTIVE);
#   elif defined(MEM_LINUX)
	struct stat sb = {};
	char path_buffer[64];
	memset(path_buffer, 0x0, sizeof(path_buffer));
	snprintf(path_buffer, sizeof(path_buffer), "/proc/%i", process.pid);
	stat(path_buffer, &sb);
	ret = (bool_t)S_ISDIR(sb.st_mode);
#	endif

	return ret;
}

mem::bool_t mem::ex::read(process_t process, voidptr_t src, voidptr_t dst, size_t size)
{
	mem::bool_t ret = MEM_FALSE;
	if (!process.is_valid()) return ret;
#	if defined(MEM_WIN)
	ret = (bool_t)(ReadProcessMemory(process.handle, (LPCVOID)src, (LPVOID)dst, (SIZE_T)size, NULL) != 0);
#	elif defined(MEM_LINUX)
	struct iovec iosrc = {};
	struct iovec iodst = {};
	iodst.iov_base = dst;
	iodst.iov_len = size;
	iosrc.iov_base = src;
	iosrc.iov_len = size;
	ret = (bool_t)((size_t)process_vm_readv(process.pid, &iodst, 1, &iosrc, 1, 0) == size);
#	endif

	return ret;
}

mem::bool_t mem::ex::write(process_t process, voidptr_t dst, voidptr_t src, size_t size)
{
	mem::bool_t ret = MEM_FALSE;
	if (!process.is_valid()) return ret;
#	if defined(MEM_WIN)
	ret = (bool_t)(WriteProcessMemory(process.handle, (LPVOID)dst, (LPCVOID)src, (SIZE_T)size, NULL) != 0);
#	elif defined(MEM_LINUX)
	struct iovec iosrc = {};
	struct iovec iodst = {};
	iosrc.iov_base = src;
	iosrc.iov_len  = size;
	iodst.iov_base = dst;
	iodst.iov_len  = size;
	ret = (bool_t)((size_t)process_vm_writev(process.pid, &iosrc, 1, &iodst, 1, 0) == size);
#	endif

	return ret;
}

mem::bool_t mem::ex::set(process_t process, voidptr_t dst, byte_t byte, size_t size)
{
	bool_t ret = MEM_FALSE;
	byte_t* data = new byte_t[size];
	memset(data, byte, size);
	ret = ex::write(process, dst, data, size);
	delete[] data;
	return ret;
}

mem::voidptr_t mem::ex::syscall(process_t process, int_t syscall_n, voidptr_t arg0, voidptr_t arg1, voidptr_t arg2, voidptr_t arg3, voidptr_t arg4, voidptr_t arg5)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
	if (!process.is_valid()) return ret;
#	if defined(MEM_WIN)
#	elif defined(MEM_LINUX)
	int status;
    struct user_regs_struct old_regs, regs;
    voidptr_t injection_addr = (voidptr_t)MEM_BAD;
    byte_t injection_buf[] =
    {
#       if defined(MEM_86)
        0xcd, 0x80, //int80 (syscall)
#       elif defined(MEM_64)
        0x0f, 0x05, //syscall
#       endif
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90, //nop
		0x90  //nop
    };

    uintptr_t old_data;
	uintptr_t injection_buffer;
	memcpy(&injection_buffer, injection_buf, sizeof(injection_buffer));
    ptrace(PTRACE_ATTACH, process.pid, MEM_NULL, MEM_NULL);
    wait(&status);

    ptrace(PTRACE_GETREGS, process.pid, MEM_NULL, &old_regs);
    regs = old_regs;

#   if defined(MEM_86)
    regs.eax = (uintptr_t)syscall_n;
    regs.ebx = (uintptr_t)arg0;
    regs.ecx = (uintptr_t)arg1;
    regs.edx = (uintptr_t)arg2;
    regs.esi = (uintptr_t)arg3;
    regs.edi = (uintptr_t)arg4;
    regs.ebp = (uintptr_t)arg5;
    injection_addr = (voidptr_t)regs.eip;
#   elif defined(MEM_64)
    regs.rax = (uintptr_t)syscall_n;
    regs.rdi = (uintptr_t)arg0;
    regs.rsi = (uintptr_t)arg1;
    regs.rdx = (uintptr_t)arg2;
    regs.r10 = (uintptr_t)arg3;
    regs.r8  = (uintptr_t)arg4;
    regs.r9  = (uintptr_t)arg5;
    injection_addr = (voidptr_t)regs.rip;
#   endif

	old_data = (uintptr_t)ptrace(PTRACE_PEEKDATA, process.pid, (void*)((uintptr_t)injection_addr), MEM_NULL);
	ptrace(PTRACE_POKEDATA, process.pid, (void*)((uintptr_t)injection_addr), (injection_buffer));

    ptrace(PTRACE_SETREGS, process.pid, MEM_NULL, &regs);
    ptrace(PTRACE_SINGLESTEP, process.pid, MEM_NULL, MEM_NULL);
    waitpid(process.pid, &status, WSTOPPED);
    ptrace(PTRACE_GETREGS, process.pid, MEM_NULL, &regs);
#   if defined(MEM_86)
    ret = (voidptr_t)regs.eax;
#   elif defined(MEM_64)
    ret = (voidptr_t)regs.rax;
#   endif

	ptrace(PTRACE_POKEDATA, process.pid, (void*)((uintptr_t)injection_addr), (old_data));

    ptrace(PTRACE_SETREGS, process.pid, MEM_NULL, &old_regs);
    ptrace(PTRACE_DETACH, process.pid, MEM_NULL, MEM_NULL);
#	endif
	return ret;
}

mem::bool_t mem::ex::protect(process_t process, voidptr_t src, size_t size, prot_t protection)
{
	bool_t ret = MEM_FALSE;
	if (!process.is_valid()) return ret;
#	if defined(MEM_WIN)
	DWORD old_protect = 0;
	if (process.handle == (HANDLE)INVALID_HANDLE_VALUE || src <= (voidptr_t)MEM_NULL || size == 0 || protection <= 0) return ret;
	ret = (bool_t)(VirtualProtectEx(process.handle, (LPVOID)src, (SIZE_T)size, (DWORD)protection, &old_protect) != 0);
#	elif defined(MEM_LINUX)
	ret = (bool_t)(ex::syscall(process, __NR_mprotect, src, (voidptr_t)size, (voidptr_t)(uintptr_t)protection, NULL, NULL, NULL) == 0);
#	endif
	return ret;
}

mem::voidptr_t mem::ex::allocate(process_t process, size_t size, prot_t protection)
{
	voidptr_t alloc_addr = (voidptr_t)MEM_BAD;
	if (!process.is_valid() || protection == 0) return alloc_addr;
#   if defined(MEM_WIN)
	alloc_addr = (voidptr_t)VirtualAllocEx(process.handle, NULL, size, MEM_COMMIT | MEM_RESERVE, protection);
	if (alloc_addr == (voidptr_t)NULL)
		alloc_addr = (voidptr_t)MEM_BAD;
#   elif defined(MEM_LINUX)
	int_t syscall_n = -1;

#   if defined(MEM_86)
	syscall_n = __NR_mmap2;
#   elif defined(MEM_64)
	syscall_n = __NR_mmap;
#   endif

	alloc_addr = (voidptr_t)(ex::syscall(process, syscall_n, (voidptr_t)0, (voidptr_t)size, (voidptr_t)(uintptr_t)protection, (voidptr_t)(MAP_PRIVATE | MAP_ANON), (voidptr_t)-1, (voidptr_t)0));
	if ((uintptr_t)alloc_addr >= (uintptr_t)-100) //error check
		alloc_addr = (voidptr_t)MEM_BAD;

#   endif
	return alloc_addr;
}

mem::bool_t mem::ex::deallocate(process_t process, voidptr_t src, size_t size)
{
	bool_t ret = MEM_FALSE;
	if (!process.is_valid()) return ret;
#   if defined(MEM_WIN)
	ret = (bool_t)(VirtualFreeEx(process.handle, src, 0, MEM_RELEASE) != 0);
#   elif defined(MEM_LINUX)
	ret = (int_t)(ex::syscall(process, __NR_munmap, src, (voidptr_t)size, NULL, NULL, NULL, NULL) != MAP_FAILED);
#   endif

	return ret;
}

mem::voidptr_t mem::ex::scan(process_t process, data_t data, voidptr_t start, voidptr_t stop)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
	if (!process.is_valid() || (uintptr_t)stop < (uintptr_t)start) return ret;

	for (uintptr_t i = (uintptr_t)start; (uintptr_t)(i + data.size()) <= (uintptr_t)stop; i++)
	{
		::size_t data_size = data.size();
		byte_t* buffer = new byte_t[data_size];
		std::memset(buffer, 0x0, data_size);
		ex::read(process, (voidptr_t)i, (voidptr_t)buffer, (mem::size_t)data_size);
		if (!std::memcmp(data.data(), buffer, data_size))
		{
			ret = (voidptr_t)i;
			break;
		}
	}

	return ret;
}

mem::voidptr_t mem::ex::pattern_scan(process_t process, data_t pattern, string_t mask, voidptr_t start, voidptr_t stop)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
	if (!process.is_valid() || (uintptr_t)stop < (uintptr_t)start || pattern.size() != mask.length()) return ret;
	mask = mem::parse_mask(mask);

	for (uintptr_t i = (uintptr_t)start; (uintptr_t)(i + pattern.size()) <= (uintptr_t)stop; i++)
	{
		::size_t data_size = pattern.size();
		byte_t* buffer = new byte_t[data_size];
		std::memset(buffer, 0x0, data_size);
		ex::read(process, (voidptr_t)i, (voidptr_t)buffer, (mem::size_t)data_size);
		bool_t good = MEM_TRUE;
		for (::size_t j = 0; j < data_size; j++)
		{
			good &= (bool_t)(
				mask[j] == MEM_UNKNOWN_BYTE ||
				buffer[j] == pattern[j]
			);

			if (!good) break;
		}

		if (good)
		{
			ret = (voidptr_t)i;
			break;
		}
	}

	return ret;
}

mem::module_t mem::ex::load_library(process_t process, lib_t lib)
{
	module_t mod = module_t();
	if (!process.is_valid() || !lib.is_valid()) return mod;
#   if defined(MEM_WIN)
	size_t buffer_size = (size_t)((lib.path.length() + 1) * sizeof(char_t));
	prot_t protection = PAGE_EXECUTE_READWRITE;
	voidptr_t libpath_ex = ex::allocate(process, buffer_size, protection);
	if (!libpath_ex || libpath_ex == (voidptr_t)-1) return mod;
	ex::set(process, libpath_ex, 0x0, buffer_size);
	ex::write(process, libpath_ex, (voidptr_t)lib.path.c_str(), buffer_size);
	HANDLE h_thread = (HANDLE)CreateRemoteThread(process.handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, libpath_ex, 0, 0);
	if (!h_thread || h_thread == INVALID_HANDLE_VALUE) return mod;
	WaitForSingleObject(h_thread, -1);
	CloseHandle(h_thread);
	VirtualFreeEx(process.handle, libpath_ex, 0, MEM_RELEASE);
	mod = ex::get_module(process, lib.path);
#   elif defined(MEM_LINUX)
	string_t libc_str = "/libc.so";
	module_t libc_ex  = ex::get_module(process, libc_str);
	if(!libc_ex.is_valid())
	{
		libc_str = "/libc-";
		libc_ex  = ex::get_module(process, libc_str);
		if(!libc_ex.is_valid())
			return mod;
	}

	lib_t libc_load = lib_t(libc_ex.path, RTLD_LAZY);
	module_t libc_in = in::load_library(libc_load);
	if(!libc_in.is_valid())
		return mod;

	voidptr_t dlopen_ex = (voidptr_t)(
		(uintptr_t)libc_ex.base +
		(uintptr_t)in::get_symbol(libc_in, "__libc_dlopen_mode") - (uintptr_t)libc_in.base
	);

	//---

	byte_t inj_buf[] =
    {
#       if defined(MEM_86)
        0x51,       //push ecx
        0x53,       //push ebx
        0xFF, 0xD0, //call eax
        0xCC,       //int3 (SIGTRAP)
#       elif defined(MEM_64)
        0xFF, 0xD0, //call rax
        0xCC,       //int3 (SIGTRAP)
#       endif
    };

    size_t path_size = lib.path.size();
    size_t inj_size  = sizeof(inj_buf) + path_size;
    voidptr_t inj_addr = ex::allocate(process, inj_size, PROT_EXEC | PROT_READ | PROT_WRITE);
    if(inj_addr == (voidptr_t)MEM_BAD) return mod;
    voidptr_t path_addr = (voidptr_t)((uintptr_t)inj_addr + sizeof(inj_buf));
    ex::write(process, inj_addr, (voidptr_t)inj_buf, sizeof(inj_buf));
    ex::write(process, path_addr, (voidptr_t)lib.path.c_str(), path_size);

    int status;
    struct user_regs_struct old_regs, regs;
    module_handle_t handle = (voidptr_t)-1;

    ptrace(PTRACE_ATTACH, process.pid, MEM_NULL, MEM_NULL);
    wait(&status);
    ptrace(PTRACE_GETREGS, process.pid, MEM_NULL, &old_regs);

    regs = old_regs;

#   if defined(MEM_86)
    regs.eax = (intptr_t)dlopen_ex;
    regs.ebx = (intptr_t)path_addr;
    regs.ecx = (intptr_t)lib.mode;
    regs.eip = (intptr_t)inj_addr;
#   elif defined(MEM_64)
    regs.rax = (uintptr_t)dlopen_ex;
    regs.rdi = (uintptr_t)path_addr;
    regs.rsi = (uintptr_t)lib.mode;
    regs.rip = (uintptr_t)inj_addr;
#   endif

    ptrace(PTRACE_SETREGS, process.pid, MEM_NULL, &regs);
    ptrace(PTRACE_CONT, process.pid, MEM_NULL, MEM_NULL);
    waitpid(process.pid, &status, WSTOPPED);
    ptrace(PTRACE_GETREGS, process.pid, MEM_NULL, &regs);

#   if defined(MEM_86)
    handle = (module_handle_t)regs.eax;
#   elif defined(MEM_64)
    handle = (module_handle_t)regs.rax;
#   endif

    if(handle == (module_handle_t)dlopen_ex || (uintptr_t)handle > (uintptr_t)-256)
        handle = (module_handle_t)MEM_BAD;

    ptrace(PTRACE_SETREGS, process.pid, MEM_NULL, &old_regs);
    ptrace(PTRACE_DETACH, process.pid, MEM_NULL, MEM_NULL);

    //---

    ex::deallocate(process, inj_addr, inj_size);
    mod = ex::get_module(process, lib.path);
    mod.handle = handle;

#	endif

	return mod;
}

mem::voidptr_t mem::ex::get_symbol(module_t mod, const char* symbol)
{
	voidptr_t addr = (voidptr_t)MEM_BAD;
	if (!mod.is_valid()) return addr;

	lib_t lib = lib_t(mod.path);
	module_t mod_in = in::load_library(lib);
	if (!mod_in.is_valid()) return addr;
	voidptr_t addr_in = in::get_symbol(mod_in, symbol);
	if (!addr_in || addr_in == (voidptr_t)MEM_BAD) return addr;
	addr = (voidptr_t)(
		(uintptr_t)mod.base +
		((uintptr_t)addr_in - (uintptr_t)mod_in.base)
	);

	return addr;
}

//in

mem::pid_t mem::in::get_pid()
{
	pid_t pid = (pid_t)MEM_BAD;
#   if defined(MEM_WIN)
	pid = (pid_t)GetCurrentProcessId();
#   elif defined(MEM_LINUX)
	pid = (pid_t)getpid();
#   endif
	return pid;
}

mem::process_t mem::in::get_process()
{
	process_t process = process_t();
	process.pid = in::get_pid();
	process.name = in::get_process_name();
#   if defined(MEM_WIN)
	process.handle = GetCurrentProcess();
#   elif defined(MEM_LINUX)
#   endif
	return process;
}

mem::string_t mem::in::get_process_name()
{
	string_t process_name = string_t();
#   if defined(MEM_WIN)
	char_t buffer[MAX_PATH];
	GetModuleFileName(MEM_NULL, buffer, sizeof(buffer) / sizeof(char_t));
	process_name = buffer;
	process_name = process_name.substr(process_name.rfind(MEM_STR("\\")) + 1);
#   elif defined(MEM_LINUX)
	process_name = ex::get_process_name(in::get_pid());
#   endif
	return process_name;
}

mem::module_t mem::in::get_module(string_t module_name)
{
	module_t mod = module_t();
#   if defined(MEM_WIN)
	MODULEINFO module_info = {};
	HMODULE hmod = GetModuleHandle(module_name.c_str());
	HANDLE cur_handle = in::get_process().handle;
	if (hmod == MEM_NULL) return mod;
	char_t path_buffer[MAX_PATH];
	GetModuleInformation(cur_handle, hmod, &module_info, sizeof(module_info));
	GetModuleFileName(hmod, path_buffer, sizeof(path_buffer) / sizeof(char_t));
	mod.path = path_buffer;
	mod.name = mod.path.substr(mod.path.rfind(MEM_STR("\\")) + 1);
	mod.base = (voidptr_t)module_info.lpBaseOfDll;
	mod.size = (size_t)module_info.SizeOfImage;
	mod.end  = (voidptr_t)((uintptr_t)mod.base + mod.size);
	mod.handle = hmod;
#   elif defined(MEM_LINUX)
	process_t process = in::get_process();
	mod = ex::get_module(process, module_name);
    mod.handle = dlopen(mod.path.c_str(), RTLD_LAZY);
#   endif
	return mod;
}

mem::module_list_t mem::in::get_module_list()
{
	return ex::get_module_list(in::get_process());
}

mem::page_t mem::in::get_page(voidptr_t src)
{
	page_t page = page_t();
#   if defined(MEM_WIN)
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery(src, &mbi, sizeof(mbi));
	page.base = (voidptr_t)mbi.BaseAddress;
	page.size = (uintptr_t)mbi.RegionSize;
	page.end  = (voidptr_t)((uintptr_t)page.base + page.size);
	page.protection = mbi.Protect;
	page.flags = mbi.Type;
#   elif defined(MEM_LINUX)
	page = ex::get_page(in::get_process(), src);
#   endif
	return page;
}

mem::bool_t mem::in::read(voidptr_t src, voidptr_t dst, size_t size)
{
	memcpy(dst, src, size);
	return true;
}

mem::bool_t mem::in::write(voidptr_t dst, voidptr_t src, size_t size)
{
	memcpy(dst, src, size);
	return true;
}

mem::bool_t mem::in::set(voidptr_t src, byte_t byte, size_t size)
{
	memset(src, byte, size);
	return true;
}

mem::voidptr_t mem::in::scan(data_t data, voidptr_t start, voidptr_t stop)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
	if ((uintptr_t)start > (uintptr_t)stop) return ret;

	for (byte_t* p_cur = (byte_t*)start; (uintptr_t)(&p_cur[data.size()]) <= (uintptr_t)stop; p_cur = &p_cur[1])
	{
		if (!memcmp(p_cur, data.data(), data.size()))
		{
			ret = (voidptr_t)p_cur;
			break;
		}
	}

	return ret;
}

mem::voidptr_t mem::in::pattern_scan(data_t pattern, string_t mask, voidptr_t start, voidptr_t stop)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
	if ((uintptr_t)start > (uintptr_t)stop || pattern.size() != mask.length()) return ret;

	for (byte_t* p_cur = (byte_t*)start; (uintptr_t)(&p_cur[pattern.size()]) <= (uintptr_t)stop; p_cur = &p_cur[1])
	{
		bool_t good = MEM_TRUE;
		for (::size_t i = 0; i < pattern.size(); i++)
		{
			good &= (bool_t)(
				mask[i] == MEM_UNKNOWN_BYTE ||
				p_cur[i] == pattern[i]
			);

			if (!good) break;
		}

		if (good)
		{
			ret = (voidptr_t)p_cur;
			break;
		}
	}

	return ret;
}

mem::voidptr_t mem::in::syscall(int_t syscall_n, voidptr_t arg0, voidptr_t arg1, voidptr_t arg2, voidptr_t arg3, voidptr_t arg4, voidptr_t arg5)
{
	voidptr_t ret = (voidptr_t)MEM_BAD;
#   if defined(MEM_WIN)
#   elif defined(MEM_LINUX)
	ret = (voidptr_t)syscall(syscall_n, arg0, arg1, arg2, arg3, arg4, arg5);
#   endif
	return ret;
}

mem::int_t mem::in::protect(voidptr_t src, size_t size, prot_t protection)
{
	int_t ret = (int_t)MEM_BAD;
	if (src == (voidptr_t)MEM_BAD || size == (size_t)MEM_BAD || size == 0 || protection == (prot_t)MEM_BAD) return ret;
#   if defined(MEM_WIN)
	prot_t old_protection = 0;
	ret = (int_t)VirtualProtect((LPVOID)src, (SIZE_T)size, (DWORD)protection, &old_protection);
#   elif defined(MEM_LINUX)
	uintptr_t page_size = mem::get_page_size();
	uintptr_t round = ((uintptr_t)src % page_size);
	uintptr_t src_page = (uintptr_t)src - round;
	ret = (int_t)mprotect((void*)src_page, size + round, protection);
#   endif
	return ret;
}

mem::voidptr_t mem::in::allocate(size_t size, prot_t protection)
{
	voidptr_t addr = (voidptr_t)MEM_BAD;
#   if defined(MEM_WIN)
	addr = (voidptr_t)VirtualAlloc(MEM_NULL, (SIZE_T)size, MEM_COMMIT | MEM_RESERVE, protection);
#   elif defined(MEM_LINUX)
	addr = (voidptr_t)mmap(MEM_NULL, size, protection, MAP_PRIVATE | MAP_ANON, -1, 0);
#   endif

	return addr;
}

mem::bool_t mem::in::deallocate(voidptr_t src, size_t size)
{
	bool_t ret = MEM_FALSE;
#   if defined(MEM_WIN)
	VirtualFree(src, 0, MEM_RELEASE);
#   elif defined(MEM_LINUX)
	munmap(src, size);
#   endif

	ret = MEM_TRUE;
	return ret;
}

mem::module_t mem::in::load_library(lib_t lib)
{
	module_t mod = module_t();
	if (!lib.is_valid()) return mod;
#   if defined(MEM_WIN)
	HMODULE h_mod = LoadLibrary(lib.path.c_str());
	mod = in::get_module(lib.path.substr(lib.path.rfind(MEM_STR("\\"))));
	mod.handle = h_mod;
#   elif defined(MEM_LINUX)
	void* h_mod = dlopen(lib.path.c_str(), lib.mode);
	mod = in::get_module(lib.path);
	mod.handle = h_mod;
#   endif

	return mod;
}

mem::bool_t mem::in::unload_library(module_t mod)
{
	mem::bool_t ret = MEM_FALSE;
	if (!mod.is_valid()) return ret;

#   if defined(MEM_WIN)
	FreeLibrary(mod.handle);
#   elif defined(MEM_LINUX)
	dlclose(mod.handle);
#   endif

	ret = MEM_TRUE;
	return ret;
}

mem::voidptr_t mem::in::get_symbol(module_t mod, const char* symbol)
{
	voidptr_t addr = (voidptr_t)MEM_BAD;
	if (!mod.is_valid())
		return addr;

#   if defined(MEM_WIN)
	addr = (voidptr_t)GetProcAddress(mod.handle, symbol);
#   elif defined(MEM_LINUX)
	addr = (voidptr_t)dlsym(mod.handle, symbol);
#   endif

	return addr;
}

mem::size_t mem::in::detour_length(detour_t method)
{
	size_t ret = (size_t)MEM_BAD;
	switch (method)
	{
		case MEM_DT_M0: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD0); break;
		case MEM_DT_M1: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD1); break;
		case MEM_DT_M2: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD2); break;
		case MEM_DT_M3: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD3); break;
		case MEM_DT_M4: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD4); break;
		case MEM_DT_M5: ret = CALC_ASM_LENGTH(_MEM_DETOUR_METHOD5); break;
	}

	return ret;
}

mem::int_t mem::in::detour(voidptr_t src, voidptr_t dst, size_t size, detour_t method, byte_t** stolen_bytes)
{
	int_t ret = (int_t)MEM_BAD;
	size_t detour_size = in::detour_length(method);
	prot_t protection = (prot_t)0;
#	if defined(MEM_WIN)
	protection = PAGE_EXECUTE_READWRITE;
#	elif defined(MEM_LINUX)
	protection = PROT_EXEC | PROT_READ | PROT_WRITE;
#	endif
	if (detour_size == (size_t)MEM_BAD || size < detour_size || in::protect(src, size, protection) == MEM_BAD) return ret;

	if (stolen_bytes != (byte_t**)NULL)
	{
		*stolen_bytes = new byte_t[size];
		for (size_t i = 0; i < size; i++)
			* stolen_bytes[i] = ((byte_t*)src)[i];
	}

	switch (method)
	{
		case MEM_DT_M0:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD0);
	#		if defined(MEM_86)
			*(uintptr_t*)((uintptr_t)detour_buffer + 1) = (uintptr_t)dst;
	#		elif defined(MEM_64)
			*(uintptr_t*)((uintptr_t)detour_buffer + 2) = (uintptr_t)dst;
	#		endif
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		case MEM_DT_M1:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD1);
			*(dword_t*)((uintptr_t)detour_buffer + 1) = (dword_t)((uintptr_t)dst - (uintptr_t)src - detour_size);
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		case MEM_DT_M2:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD2);
	#		if defined(MEM_86)
			* (uintptr_t*)((uintptr_t)detour_buffer + 1) = (uintptr_t)dst;
	#		elif defined(MEM_64)
			*(uintptr_t*)((uintptr_t)detour_buffer + 2) = (uintptr_t)dst;
	#		endif
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		case MEM_DT_M3:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD3);
			*(dword_t*)((uintptr_t)detour_buffer + 1) = (dword_t)((uintptr_t)dst - (uintptr_t)src - detour_size);
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		case MEM_DT_M4:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD4);
	#		if defined(MEM_86)
			* (uintptr_t*)((uintptr_t)detour_buffer + 1) = (uintptr_t)dst;
	#		elif defined(MEM_64)
			*(uintptr_t*)((uintptr_t)detour_buffer + 2) = (uintptr_t)dst;
	#		endif
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		case MEM_DT_M5:
		{
			byte_t detour_buffer[] = ASM_GENERATE(_MEM_DETOUR_METHOD5);
			*(dword_t*)((uintptr_t)detour_buffer + 1) = (dword_t)((uintptr_t)dst - (uintptr_t)src - detour_size);
			in::write(src, detour_buffer, sizeof(detour_buffer));
			break;
		}

		default:
		{
			return ret;
			break;
		}
	}

	ret = (int_t)MEM_GOOD;
	return ret;
}

mem::voidptr_t mem::in::detour_trampoline(voidptr_t src, voidptr_t dst, size_t size, detour_t method, byte_t** stolen_bytes)
{
	voidptr_t gateway = (voidptr_t)MEM_BAD;
	size_t detour_size = in::detour_length(method);
	prot_t protection = (prot_t)0;
#   if defined(MEM_WIN)
	protection = PAGE_EXECUTE_READWRITE;
#   elif defined(MEM_LINUX)
	protection = PROT_EXEC | PROT_READ | PROT_WRITE;;
#   endif

	if (detour_size == (size_t)MEM_BAD || size < detour_size || in::protect(src, size, protection) == MEM_BAD) return gateway;
	size_t gateway_size = size + detour_size;
	gateway = in::allocate(gateway_size, protection);
	if (!gateway || gateway == (voidptr_t)MEM_BAD) return (voidptr_t)MEM_BAD;
	in::set(gateway, 0x0, gateway_size);
	in::write(gateway, src, size);
	in::detour((voidptr_t)((uintptr_t)gateway + size), (voidptr_t)((uintptr_t)src + size), detour_size, method);
	in::detour(src, dst, size, method, stolen_bytes);

	return gateway;
}

mem::bool_t mem::in::detour_restore(voidptr_t src, byte_t* stolen_bytes, size_t size)
{
	bool_t ret = MEM_FALSE;
	prot_t protection = (prot_t)0;
#   if defined(MEM_WIN)
	protection = PAGE_EXECUTE_READWRITE;
#   elif defined(MEM_LINUX)
	protection = PROT_EXEC | PROT_READ | PROT_WRITE;
#   endif
	if (in::protect(src, size, protection) != MEM_BAD)
		in::write(src, (voidptr_t)stolen_bytes, (size_t)size);

	ret = MEM_TRUE;
	return ret;
}

#endif //MEM_COMPATIBLE
