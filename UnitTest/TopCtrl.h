#if !defined (TOPCTRL_H)
#define TOPCTRL_H
//-----------------------------
//  (c) Reliable Software, 2005
//-----------------------------
#include <Win/Controller.h>
#include <Win/Message.h>
#include <Ctrl/Edit.h>
#include <Sys/Timer.h>

class Watch;
class FWatcher;

class TopCtrl: public Win::Controller
{
public:
	TopCtrl ();
	~TopCtrl ();
	bool OnCreate (Win::CreateData const * create, bool & success) ;
	bool OnDestroy () ;
	bool OnSize (int width, int height, int flag) ;
	bool OnRegisteredMessage (Win::Message & msg) ;
	bool OnUserMessage (Win::UserMessage & msg) ;
	bool OnTimer (int id) ;

	void FolderChange (FWatcher * watcher);
private:
	void OnInit ();
private:
	bool							_ready;
	Win::RegisteredMessage			_initMsg;
	Win::StreamEdit					_output;
	std::auto_ptr<Watch>			_watch;
	Win::Timer						_timer;
};


#endif
