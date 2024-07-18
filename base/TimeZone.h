#ifndef __FeCountry_H__
#define __FeCountry_H__

#pragma once

#include <QtCore/QString>
#include <QtCore/QList>
#include "Currency.h"
#include "base_api.h"

#define TIMEZONE_CODE_ENUM(declare)\
        declare(TIMEZONE_UNKNOW, "UNKOWN", "INVALID" "UNKNOWN")\
        declare(TIMEZONE_CST, "IST", "INDIAN_STANDARD_TIME", "Asia/Mumbai")\
        declare(TIMEZONE_EST, "EST", "EASTERN_STANDARD_TIME", "America/New_York")\
        declare(TIMEZONE_PST, "PST", "PACIFIC_STANDARD_TIME", "America/Los_Angeles")\
        declare(TIMEZONE_UTC, "UTC", "GREENWICH_TIME", "Atlantic/Reykjavik")

enum TimezoneCode {TIMEZONE_CODE_ENUM(SELECT_1_AND_COMMA_IN_4) COUNTRY_MAX};
BASE_API const char* timezoneShortName(TimezoneCode);
BASE_API const char* timezoneLongName(TimezoneCode);
BASE_API const char* timezoneSessionName(TimeZoneCode);
BASE_API TimezoneCode timezoneCodeFromShortName(const char* timezoneShortName);
BASE_API TimezoneCode timezoneCodeFromSessionNam(const char* timezoneSessionName);

#endif