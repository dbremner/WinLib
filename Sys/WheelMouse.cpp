//
// (c) Reliable Software 1997, 1998
//

#include <WinLibBase.h>
#include "SysVer.h"
#include "WheelMouse.h"

//
// Microsoft IntelliMouse Support
//

IntelliMouse::IntelliMouse ()
    : _hwndWheel (0),
      _msgMouseWheel (0),
      _msg3DSupport (0),
      _msgScrollLines (0),
      _f3DSupport (FALSE),
      _wheelScrollLines (3)
{
    // Figure out how to use IntelliMouse

    // Built-in support
	_msgMouseWheel = WM_MOUSEWHEEL;
	// Revisit: documentation says that this should work under Win98 & NT 4.0
	// but SPI_GETWHEELSCROLLLINES constant is defined only under NT
	//::SystemParametersInfo (SPI_GETWHEELSCROLLLINES, 0, &_wheelScrollLines, FALSE);
}   
