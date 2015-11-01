#if !defined (ABOUT_H)
#define ABOUT_H
//----------------------------
// (c) Reliable Software, 2005
//----------------------------

#include "Resource/resource.h"
#include <Win/Dialog.h>

class AboutDlgHandler : public Dialog::ControlHandler
{
public:
	AboutDlgHandler () : Dialog::ControlHandler (IDD_ABOUT) {}
	bool OnInitDialog () ;
    bool OnDlgControl (unsigned ctrlId, unsigned notifyCode);
	bool OnApply ();
};

#endif
