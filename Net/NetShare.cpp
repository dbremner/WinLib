//---------------------------
// (c) Reliable Software 2000
//---------------------------
#include <WinLibBase.h>
#include "NetShare.h"
#include "NetShareNT.h"
#include "ShareEx.h"
#include <Sys/SysVer.h>

using namespace Net;

Share::Share ()
{
	_impl.reset (new Net::ShareNT ());
}

void Share::Add (Net::SharedObject const & object) 
{
	try
	{
		_impl->Add (object);
	}
	catch (Net::ShareException & e)
	{
		Win::ClearError ();
		throw Win::Exception (e.GetMessage (), e.GetReason ());
	}
}

void Share::Delete (std::string const & netname)
{
	try
	{
		_impl->Delete (netname);
	}
	catch (Net::ShareException & e)
	{
		Win::ClearError ();
		throw Win::Exception (e.GetMessage (), e.GetReason ());
	}
}

