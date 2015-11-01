//------------------------------------
//  (c) Reliable Software, 2004 - 2008
//------------------------------------

#include "CmdVector.h" // CmdVector is a typedef, not a class
#include "Modeless.h"

#include <Win/Controller.h>
#include <Win/Message.h>
#include <Ctrl/Accelerator.h>
#include <Com/DragDrop.h>

namespace Win { class MessagePrepro; }
namespace Hierarchy { class Controller; }
class Commander;
class View;

class TopCtrl: public Win::Controller, public Win::FileDropSink
{
public:
	TopCtrl (char const * cmdLine, Win::MessagePrepro & msgPrepro);
	~TopCtrl ();

	Win::MessagePrepro & GetMessagePrepro () { return _msgPrepro; }

	Notify::Handler * GetNotifyHandler (Win::Dow::Handle winFrom, unsigned idFrom);
	bool OnCreate (Win::CreateData const * create, bool & success);
	bool OnDestroy ();
	bool OnSize (int width, int height, int flag);
	bool OnRegisteredMessage (Win::Message & msg);
	bool OnInitPopup (Menu::Handle menu, int pos);
	bool OnMenuSelect (int id, Menu::State state, Menu::Handle menu);
	bool OnCommand (int cmdId, bool isAccel);

	Win::Dow::Handle GetTargetWnd () const { return GetWindow ();}
	void OnFileDrop (Win::FileDropHandle droppedFiles, Win::Point dropPoint);

private:
	void OnInit ();
	void MenuCommand (int cmdId);

private:
	Com::UseOle						_oleUser;
	bool							_ready;
	std::string						_cmdLine;
	Win::MessagePrepro			  & _msgPrepro;
	Win::RegisteredMessage			_initMsg;
	Win::RegisteredMessage			_fileDropMsg;
	std::auto_ptr<Commander>		_commander;
	std::auto_ptr<CmdVector>		_cmdVector;
	std::auto_ptr<Accel::Handler>	_kbdAccel;
	std::auto_ptr<Menu::DropDown>	_menu;
	std::auto_ptr<View>				_view;
	ModelessManager					_modelessMan;
};
