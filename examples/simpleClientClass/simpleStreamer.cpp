#include "simpleClient.h"

void SimpleStreamer::on_connected()
  {
	_lock.lock();
	_cond.notify_all();
	_connect_finish = true;
	_connected = true;
	_lock.unlock();

  }

  void SimpleStreamer::on_close()
  {
	_connected = false;
  }

  void SimpleStreamer::on_fail()
  {
	_lock.lock();
	_cond.notify_all();
	_connect_finish = true;
	_connected = false;
	_lock.unlock()
  }

public:

  connection_listener():
  {
  }

  bool SimpleStreamer::connect(std::string url)
  {
	h.set_open_listener(&on_connected);
	h.set_close_litener(&on_close);
	h.set_fail_listener(&on_fail);
	h.connect(url);
	_lock.lock();
	if(!_connect_finish)
	  {
		_cond.wait(_lock);
	  }
	_lock.unlock();
	return _connected;
  }

  void SimpleStreamer::close()
  {
	h.sync_close();
	h.clear_con_listeners();
  }

  bool SimpleStreamer::sendBuffer(std::string name, char* buff)
  {
	if(_connected)
	  {
		h.socket()->emit(name, std::make_shared<std::string>(buff,sizeof(buff)));
	  }
	return _connected;
  }

  bool SimpleStreamer::sendMessage(std::string name, std::string message)
  {
	if(_connected)
	  {
		h.socket()->emit(name, message);
	  }
	return _connected;
  }

  bool isConnected()
  {
	return _connected;
  }

};

