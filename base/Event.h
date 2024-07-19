#pragma once
#include <QtCore/QSharedPointer>
#include "base/base_api.h"

class BASE_API  Event{
    public:
        virtual ~Event();
        int type() const;
    protected:
        Event(int type);
    private:
        const int _type;
};

typedef QSharedPointer<Event> EventPtr;

template<class _Ty, int _EvtType>
class DateEvent :public Event{
    public:
        DateEvent(const _Ty& data) :Event(_EvtType), _data(data){}
        virtual ~DataEvent(){}
        _Ty data() const{return _datal;}
    private:
        _Ty _data;
};