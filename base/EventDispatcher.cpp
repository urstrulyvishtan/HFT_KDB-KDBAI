#include "EventDispatcher.h"
#include "EventQueue.h"

EventDispatcher::EventDispatcher(EventQueue* queue)
            :NotifiableObserver<EventCallback, EventPtr>(&EventCallback::onEvent),_queue(queue){}

EventDispatcher::~EventDispatcher(){}

EventDispatcher * EventDispatcher::defaultDispatcher(){
    static EventDispatcher dispatcher(EventQueue::defaultQueue());
    return &dispatcher;
}

int EventDispatcher::processEvent(){
    int i = 0;
    while(EventPtr evt = _queue->pop()){
        this->notifyAll(evt);
        ++i;
    }
    return i;
}