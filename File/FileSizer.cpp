//-----------------------------------
// (c) Reliable Software 2004
//-----------------------------------
#include <WinLibBase.h>
#include "File.h"
#include <Sys/SysVer.h>

void File::InitSizer ()
{
	Assert (_hFile != INVALID_HANDLE_VALUE);

	// create implementation depending on the operating system
	_sizer.reset (new File::Sizer64 (_hFile));
}

File::Sizer64::Sizer64 (HANDLE hFile)
	: File::Sizer (hFile)
{}

bool File::Sizer64::Rewind ()
{
	File::Size zero (0, 0);
	return SetFilePointerEx (_hFile, zero.ToNative (), 0, FILE_BEGIN) != 0;
}

File::Size File::Sizer64::GetSize () const
{
	File::Size size;
	if (GetFileSizeEx (_hFile, size.ToPtr ()) == 0)
	{
		throw Win::Exception ("Get file size failed.");
	}
	return size;
}

File::Offset File::Sizer64::GetPosition () const
{
	File::Offset zero (0, 0);
	File::Offset position;
	if (SetFilePointerEx (_hFile, zero.ToNative (), position.ToPtr (), FILE_CURRENT) == 0)
	{
		DWORD lastError = ::GetLastError ();
		if (lastError == ERROR_HANDLE_EOF)
		{
			Win::ClearError ();
			position = File::Offset::Invalid;
		}
		else
			throw Win::Exception ("Cannot get file position.");
	}
	return position;
}

File::Offset File::Sizer64::SetPosition (File::Offset pos)
{
	File::Offset newPos;
	if (SetFilePointerEx (_hFile, pos.ToNative (), newPos.ToPtr (), FILE_BEGIN) == 0)
	{
		DWORD lastError = ::GetLastError ();
		if (lastError != ERROR_HANDLE_EOF)
			throw Win::Exception ("Cannot set file position.");
		else
			Win::ClearError ();
	}
	return newPos;
}

