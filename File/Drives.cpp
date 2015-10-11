// ----------------------------------
// (c) Reliable Software, 1999 - 2007
// ----------------------------------

#include <WinLibBase.h>
#include "Drives.h"
#include <Sys/SysVer.h>

DriveSeq::DriveSeq ()
	: _cur (_driveStrings.begin ()),
	  _end (_driveStrings.end ())
{
	size_t bufSize = ::GetLogicalDriveStrings (0, 0);
	std::vector<char> buffer;
	buffer.resize (bufSize);
	size_t writeSize = ::GetLogicalDriveStrings (bufSize, &buffer [0]);
	_driveStrings.Assign (&buffer [0], writeSize);

	_cur = _driveStrings.begin ();
	_end = _driveStrings.end ();
}

void WriteableDriveSeq::Advance ()
{
	do
	{
		++_cur;
	}
	while (!AtEnd () && DriveInfo (GetDriveString ()).IsCdRom ());
}

DriveInfo::DriveInfo (std::string const & rootPath)
	: _rootPath (rootPath)
{
	_type = ::GetDriveType (rootPath.c_str ());
}

int DriveInfo::MbytesFree () const
{
	int mbFree = 0;

	ULARGE_INTEGER bytesAvail, bytesTotal, bytesFree;
	GetDiskFreeSpaceExA (_rootPath.c_str (), &bytesAvail, &bytesTotal, &bytesFree);
	mbFree = (bytesAvail.HighPart << (32 - 20)) + (bytesAvail.LowPart >> 20);
	return mbFree;
}

