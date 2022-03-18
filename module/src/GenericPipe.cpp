/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "GenericPipe.h"
#include "iostream"
Message::Message(std::string _str, std::vector<float> _val) : str(_str){
  for (int i = 0; i < _val.size(); i++) {
    vals.push_back(_val[i]);
    std::cout << _val[i] << std::endl;
  }
};
Message::Message(std::string _str, int _val) :  str(_str), vals({(float)_val}) {};
Message::Message() {}

void GenericPipe::pushQueue(Message* msg) {
  _mutex.lock();
  _deque.push_back(msg);	
  _mutex.unlock();
}

Message* GenericPipe::popQueue() {
  _mutex.lock();
  static Message ret;

  if (!_deque.empty()) {
    Message* msg = _deque.front();

    ret.vals = msg->vals;
    ret.str = msg->str;

    _deque.pop_front();
    _mutex.unlock();	

    delete msg; // This may be too slow
    return &ret;
  }

  _mutex.unlock();
  return nullptr; 
}
