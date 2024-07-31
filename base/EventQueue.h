#pragma once
#include <QtCore/QMutex>
#include <Qtcore/QMutexLocker>
#include <QtCore/QList>
#include "Event.h"

class BASE_API EventQueue
{
    public:
        EventQueue();
        ~EventQueue();
        static EventQueue* defaultQueue();
        void push(const EventPtr& evt);

        EventPtr pop();
        bool isEmpty() const;

    private:
        QList<EventPtr> _pushedQueue;
        QList<EventPtr> _poppedQueue;
        mutable QMutex _mutex;
};