#pragma once

#include "NotifiableObserver.h"
#include "Event.h"

class EventCallback{
    public:
        virtual void onEvent(const EventPtr&) = 0;
};
class EventQueue;
class BASE_API EventDispatcher :public NotifiableObserver<EventCallback, EventPtr>
{
    public:
        EventDispatcher(EventQueue*);
        ~EventDispatcher();

        static EventDispatcher* defaultDispatcher();
        int processEvent();
    private:
        EventQueue* _queue;
}