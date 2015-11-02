#if !defined (NETSHARE_NT_H)
#define NETSHARE_NT_H
//---------------------------
// (c) Reliable Software 2000-04
//---------------------------
#include "NetShareImpl.h"
#include <Sys/Dll.h>
#include <lmcons.h>

namespace Net
{
	class ShareNT: public ShareImpl
	{

	public:
		ShareNT ();

		void Add (SharedObject const & object);
		void Delete (std::string const & netname);

	private:
	};
}
#endif
