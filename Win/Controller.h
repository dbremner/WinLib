#if !defined (CONTROLLER_H)
#define CONTROLLER_H
//-----------------------------------
// (c) Reliable Software 2000 -- 2005
//-----------------------------------

#include <Win/Procedure.h>
#include <Ctrl/Menu.h>
#include <Win/Utility.h>

class AppCmdHandler;
namespace Notify { class Handler; }
namespace Control { class Handler; }
namespace Keyboard { class Handler; }
namespace Win
{
	class Message;
	class UserMessage;
	class FileDropHandle;
}
namespace OwnerDraw
{
	class Item;
	class Handler;
}
namespace Dialog
{
	class ControlHandler;
}

namespace Win
{
    class Controller
    {
		friend class Maker;
	protected:
		Controller ()
			: _h (0)
		{}
		void SetWindowHandle (Win::Dow::Handle win) { _h = win; }
		virtual bool MustDestroy () 
			{ return false; }

		// For internal use only: made public because of difficulties with template friends
	public:
		static void Attach (Win::Dow::Handle win, Controller * ctrl);
		bool Dispatch (UINT message, WPARAM wParam, LPARAM lParam, LRESULT & result) ;
	public:
		virtual ~Controller ()
		{
			// detach this controller from window
			_h.SetLongPtr<Controller *> (0);
		}
		Win::Dow::Handle GetWindow () const { return _h; }
		virtual Notify::Handler * GetNotifyHandler (Win::Dow::Handle winFrom, unsigned idFrom) 
			{ return 0; }
		virtual Control::Handler * GetControlHandler (Win::Dow::Handle winFrom, unsigned idFrom) 
			{ return 0; }
		virtual Keyboard::Handler * GetKeyboardHandler () 
			{ return 0; }
		virtual Dialog::ControlHandler * GetDlgControlHandler () 
			{ return 0; }
		virtual AppCmdHandler * GetAppCmdHandler () 
			{ return 0; }
		virtual bool OnCreate (Win::CreateData const * create, bool & success) 
			{ return false; }
        virtual bool OnDestroy () 
			{ return false; }
		virtual bool OnShutdown (bool isEndOfSession, bool isLoggingOff)  { return false; }
		virtual bool OnActivateApp (unsigned long prevThreadId) 
			{ return false; }
		virtual bool OnDeactivateApp (unsigned long nextThreadId) 
			{ return false; }
		virtual bool OnActivate (bool isClickActivate, bool isMinimized, Win::Dow::Handle prevWnd) 
			{ return false; }
		virtual bool OnDeactivate (bool isMinimized, Win::Dow::Handle nextWnd) 
			{ return false; }
		virtual bool OnMouseActivate (Win::HitTest hitTest, Win::MouseActiveAction & activate) 
			{ return false; }
		virtual bool OnFocus (Win::Dow::Handle winPrev) 
			{ return false; }
		virtual bool OnKillFocus (Win::Dow::Handle winNext) 
			{ return false; }
		virtual bool OnEnable() 
			{ return false; }
		virtual bool OnDisable() 
			{ return false; }
		virtual bool OnSize (int width, int height, int flag) 
			{ return false; }
		virtual bool OnClose () 
			{ return false; }
		virtual bool OnEraseBkgnd(Win::Canvas canvas)
			{ return false; }
		virtual bool OnPaint () 
			{ return false; }
		virtual bool OnShowWindow (bool show) 
			{ return false; }			
		virtual bool OnSettingChange (Win::SystemWideFlags flags, char const * sectionName) 
			{ return false; }
		virtual bool OnVScroll (int code, int pos, Win::Dow::Handle winCtrl) 
			{ return false; }
		virtual bool OnHScroll (int code, int pos, Win::Dow::Handle winCtrl) 
			{ return false; }
		// Commands
		virtual bool OnCommand (int cmdId, bool isAccel) 
			{ return false; }
		// Controls
		virtual bool OnControl (Win::Dow::Handle control, unsigned id, unsigned notifyCode) 
			{ return false; }
		// Standard dialog buttons
		virtual bool OnApply () 
			{ return false; }
		virtual bool OnCancel () 
			{ return false; }
		virtual bool OnHelp () 
			{ return false; }

		virtual bool OnInitPopup (Menu::Handle menu, int pos) 
			{ return false; }
		virtual bool OnExitMenuLoop (bool isContextMenu) 
			{ return false; }
		virtual bool OnInitSystemPopup (Menu::Handle menu, int pos) 
			{ return false; }
		virtual bool OnPopupSelect (int idx, Menu::State state, Menu::Handle menu) 
			{ return false; }
		virtual bool OnSysMenuSelect (int id, Menu::State state, Menu::Handle menu) 
			{ return false; }
		virtual bool OnMenuSelect (int id, Menu::State state, Menu::Handle menu) 
			{ return false; }
		virtual bool OnContextMenu (Win::Dow::Handle wnd, int xPos, int yPos) 
			{ return false; }
		virtual bool OnTimer (int id) 
			{ return false; }
		virtual bool OnDialogIdle(Win::Dow::Handle dlg)
			{ return false; }
		// Mouse
		virtual bool OnMouseMove (int x, int y, Win::KeyState kState) 
			{ return false; }
		virtual bool OnWheelMouse (int zDelta) 
			{ return false; }
		virtual bool OnLButtonDown (int x, int y, Win::KeyState kState) 
			{ return false; }
		virtual bool OnLButtonUp (int x, int y, Win::KeyState kState) 
			{ return false; }
		virtual bool OnLButtonDblClick (int x, int y, Win::KeyState kState) 
			{ return false; }
		virtual bool OnCaptureChanged (Win::Dow::Handle newCaptureWin) 
			{ return false; }
		// Drop target
		virtual bool OnDropFiles (Win::FileDropHandle const & dropFile) 
			{ return false; }
		// Keyboard
		virtual bool OnChar (int vKey, int flags) 
			{ return false; }
		virtual bool OnCharToItem(int vKey, int nCaret, Win::Dow::Handle listbox)
			{ return false; }
		virtual bool OnVKeyToItem(int vKey, int nCaret, Win::Dow::Handle listbox)
			{ return false; }
		// DDE
		virtual bool OnDdeInitiate (Win::Dow::Handle client, std::string const & app, std::string const & topic) 
			{ return false; }
		// User messages
		virtual bool OnUserMessage (UserMessage & msg) 
			{ return false; }
		// Registered messages
		virtual bool OnRegisteredMessage (Message & msg) 
			{ return false; }
		// Interprocess communication
		virtual bool OnInterprocessPackage (unsigned int msg, char const * package, unsigned int errCode, long & result) throw ()
			{ return false; }

		//	Specialized drawing
		virtual bool OnMenuDraw (OwnerDraw::Item & draw) 
			{ return false; }
		virtual bool OnItemDraw (OwnerDraw::Item & draw, unsigned ctrlId) ;
		void AddDrawHandler (OwnerDraw::Handler * handler);
		void RemoveDrawHandler (Win::Dow::Handle winParent, unsigned ctrlId) ;
		// Revisit: use draw handlers to deal with these
		virtual bool OnMeasureListBoxItem(int idControl, int idx, unsigned& height) 
			{ return false; }
		virtual bool OnPreDrawEdit(Win::Dow::Handle win, Win::Canvas canvas, Brush::Handle& hbr) 
			{ return false; }
		virtual bool OnPreDrawStatic(Win::Dow::Handle win, Win::Canvas canvas, Brush::Handle& hbr) 
			{ return false; }
		virtual bool OnPreDrawListBox(Win::Dow::Handle win, Win::Canvas canvas, Brush::Handle& hbr) 
			{ return false; }

		virtual bool OnSetFont(Font::Handle font, bool fRedraw) 
			{ return false; }
		virtual bool OnTrainingCard(int, int)
			{ return false; }
		virtual bool OnAppCommand (unsigned cmd, unsigned device, unsigned virtKeys, Win::Dow::Handle window);
	protected:
		Win::Dow::Handle	_h;
		std::list<OwnerDraw::Handler *>	_drawHandlers;
		typedef std::list<OwnerDraw::Handler *>::iterator HandlerIter;
    };

	class TopController : public Controller
	{
		friend class Maker;

	protected:
		bool MustDestroy () 
			{ return true; }
	};

	class SubController : public Controller
	{
	public:
		SubController ()
			: _prevProc (0),
			  _prevController (0)
		{} 
		void Init (HWND h, ProcPtr prevProc, Controller * prevCtrl)
		{
			SetWindowHandle (h);
			_prevProc = prevProc;

			Assert(prevCtrl == 0);	//	subclassing of windows with controllers not yet supported
			_prevController = prevCtrl;
		}
		LRESULT CallPrevProc (UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::CallWindowProc (_prevProc, _h.ToNative (), message, wParam, lParam);
		}
		ProcPtr GetPrevProc ()
		{
			return _prevProc;
		}
		Controller * GetPrevController ()
		{
			return _prevController;
		}
	protected:
		ProcPtr			_prevProc;
		Controller *	_prevController;
	};
}

#endif
