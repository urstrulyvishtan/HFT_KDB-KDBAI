#include "Event.h"

Event::Event(int type)
    :_type(type){}

Event::~Event(){}

int Event::type() const{
    return _type;
}