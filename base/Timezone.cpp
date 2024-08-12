#include "TimeZone.h"
#include <QtCore/QHash>
#include <QtCore/QStringList>

const char * timezoneShortName(TimezoneCode timezone){
    static const char* names[]={
        TIMEZONE_CODE_ENUM(SELECT_2_AND_COMMA_IN_4)
    };
    if(timezone>=0 && timezone<ARRAY_SIZE(names)){
        return names[timezone];
    }else{
        return names[0];
    }
}

const char * timezoneLongName(TimezoneCode timezone){
    static const char* names[]={
        TIMEZONE_CODE_ENUM(SELECT_3_AND_COMMA_IN_4)
    };
    if(timezone>=0 && timezone<ARRAY_SIZE(names)){
        return names[timezone];
    }else{
        return names[0];
    }
}

const char * timezoneSessionName(TimezoneCode timezone){
    static const char* names[]={
        TIMEZONE_CODE_ENUM(SELECT_4_AND_COMMA_IN_4)
    };
    if(timezone>=0 && timezone<ARRAY_SIZE(names)){
        return names[timezone];
    }else{
        return names[0];
    }
}

TimezoneCode timezoneCodeFromShortName(const char* timezoneShortName){
    static QHash<QString, TimezoneCode> map;
    if(map.isEmpty()){
        TIMEZONE_CODE_ENUM(DEFINE_NAME_ENUM_MAP4_KEY_2);
    }
    return map[timezoneShortName];
}

TimezoneCode timezoneCodeFromSessiontName(const char * timezoneSessionName){
    static QHash<QString, TimezoneCode> map;
    if(map.isEmpty()){
        TIMEZONE_CODE_ENUM(DEFINE_NAME_ENUM_MAP4_KEY_4);
    }
    return map[timezoneSessionName];
}