#include "EventQueue.h"

EventQueue::EventQueue(){}

EventQueue::~EventQueue(){}

EventQueue * EventQueue::defaultQueue(){
    static EventQueue queue;
    return &queue;
}

void EventQueue::push(EventPtr & evt){
    QMutexLocker l(&_mutex);
    _pushedQueue.append(evt);
}

EventPtr EventQueue::pop(){
    if(_popedQueue.isEmpty()){
        QMutexLocker l(&_mutex);
        if(!_pushedQueue.isEmpty()){
            _popedQueue.swap(_pushedQueue);
        }
    }
    if(_popedQueue.isEmpty()){
        return EventPtr();
    } else{
        EventPtr evt = _popedQueue.front();
        _popedQueue.pop_front();
        return evt;
    }
}

bool EventQueue::isEmpty() const{
    if(!_popedQueue.isEmpty()){
        return false;
    }
    QMutexLocker l(&_mutex);
    return _pushedQueue.isEmpty();
}