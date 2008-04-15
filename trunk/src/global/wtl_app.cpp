
//         Copyright E�in O'Callaghan 2006 - 2007.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "stdAfx.hpp"

#include <boost/array.hpp>

#define WINVER 0x0500
#define _WIN32_WINNT 0x0500
#define _WIN32_IE 0x0500
#define _RICHEDIT_VER 0x0200
#define VC_EXTRALEAN

#ifdef WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include "wtl_app.hpp"
#include "string_conv.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
    namespace boost { namespace filesystem { namespace detail {

#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL BOOST_FILESYSTEM_DECL

#include <boost/detail/utf8_codecvt_facet.hpp>

namespace hal
{

class app_impl
{
public:
	app_impl() :
		hmod_(NULL),
		instance_(_Module.GetModuleInstance()),
		initial_path_(boost::filesystem::initial_path<boost::filesystem::wpath>())
	{
		LPWSTR *szArglist; int nArgs;		
		szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
		
		std::locale global_loc = std::locale();
		std::locale loc(global_loc, new boost::filesystem::detail::utf8_codecvt_facet);
		boost::filesystem::wpath_traits::imbue(loc);
		
		if (NULL == szArglist)
		{
		}
		else
		{
			exe_string_  = szArglist[0];
			exe_path_ = boost::filesystem::wpath(exe_string_);
			
			for (int i=1; i<nArgs; ++i) 
				command_args_.push_back(szArglist[i]);
				
			working_directory_ = exe_path_.branch_path();
		}		
		LocalFree(szArglist);	
	}

	friend class app_module;

private:
	HMODULE hmod_;
	HINSTANCE instance_;
	std::wstring exe_string_;
	std::wstring res_dll_;
	
	boost::filesystem::wpath exe_path_;
	boost::filesystem::wpath initial_path_;
	boost::filesystem::wpath working_directory_;
	
	std::vector<std::wstring> command_args_;	
};

app_module::app_module() :
	pimpl(new app_impl())
{}

const std::wstring& app_module::exe_string() const 
{ 
	return pimpl->exe_string_; 
}

const boost::filesystem::wpath& app_module::exe_path() const 
{ 
	return pimpl->exe_path_; 
}

const boost::filesystem::wpath& app_module::initial_path() const 
{ 
	return pimpl->initial_path_; 
}

const boost::filesystem::wpath& app_module::working_directory() const 
{ 
	return pimpl->working_directory_; 
}
	
const std::vector<std::wstring>& app_module::command_args() const 
{ 
	return pimpl->command_args_; 
}
	
void app_module::res_revert()
{
	if (pimpl->hmod_) FreeLibrary(pimpl->hmod_);
	_Module.SetResourceInstance(pimpl->instance_);
}

void app_module::res_set_dll(std::wstring dll)
{
	if (pimpl->hmod_) FreeLibrary(pimpl->hmod_);
	pimpl->res_dll_ = dll;
	
	HMODULE hmod_ = ::LoadLibraryEx(dll.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE);
	_Module.SetResourceInstance(reinterpret_cast<HINSTANCE>(hmod_));
}

std::wstring app_module::res_wstr(unsigned uID)
{
	// The upper size limit ain't nice, but at least it's safe from buffer overflow
	win_c_str<std::wstring> str(2048);
	
	int size = ::LoadString(_Module.GetResourceInstance(), uID, str, str.size());
	assert(size != 0);
	
	return str;
}

std::pair<void*,size_t> app_module::res_find_lock(unsigned name, unsigned type)
{
	HRSRC rsrc = FindResource(_Module.GetResourceInstance(), (LPCTSTR)name, (LPCTSTR)type);
	assert(rsrc);
	
	HGLOBAL global = LoadResource(_Module.GetResourceInstance(), rsrc);
	assert(global);
	
	void* ptr = LockResource(global);
	assert(ptr);
	
	return std::pair<void*,size_t>(ptr, SizeofResource(_Module.GetResourceInstance(), rsrc));
}

app_module& app()
{
	static app_module app;
	return app;
}

} // namespace hal
