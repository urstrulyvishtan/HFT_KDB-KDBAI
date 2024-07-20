#pragma once
#include <QtCore/QString>
#include "base/base_api.h"
#include "base/enum_ext.h"
#ifndef _WIN32
#include <values.h>
#endif

namespace mts
{
class BASE_API double{
    public:
        static bool isDoubleMax(double v);
        static bool isValidPrice(double v);
        static bool isZero(double);
        static QString toReadableString(double v, int prec=10);
        static QString toString(double v, int prec);
        static bool isEqual(double v1, double v2);
        static bool isGreaterThan(double v1, double v2);
        static bool isLessThan(double v1, double v2);
        static bool isGreaterThanEqual(double v1, double v2);
        static bool isLessThanEqual(double v1, double v2);
        static double floor(double val, int precision);
        static double ceil(double val, int precision);
        static int getPrecision(double val, int precision);
};

#define INSTRUMENT_ID_ENUM(declare)\
        declare(TYPE_UNKOWN, "UNKOWN", "UNKOWN")\
        declare(TYPE_STK_SPOT, "STK", "STOCK")\
        declare(TYPE_FUTR, "FUT", "FUTURES")\
        declare(TYPE_OPTION, "OPT", "OPTIONS")\
        declare(TYPE_INDEX, "IDX", "INDEX")\
        declare(TYPE_FX, "FX", "FOREX")\
        declare(TYPE_CFD, "CFD", "CFD")\
        declare(TYPE_BOND, "BND", "BOND")\
        declare(TYPE_FUND, "FND", "FUND")\
        declare(TYPE_WARRANT, "WRT", "WARRANT")\
        declare(TYPE_SPOT, "SPOT", "SPOT")\
        declare(TYPE_CASH, "CASH", "CASH")\
        declare(TYPE_HUOBI, "HUOBI", "HUBOI")\
        declare(TYPE_BITMEX, "BITMEX", "BitMEX")\
        declare(TYPE_OKEX, "OKEX", "OKEX")

enum InstrumentType { INSTRUMENT_ID_ENUM(SELECT_1_AND_COMMA_IN_3) INSTRUMENT_TYPE_MAX};

BASE_API const char* instrumentTypeName(InstrumentType);
BASE_API InstrumentType instrumentType(const char*);
BASE_API const char* instrumentTypeDescription(InstrumentType);

BASE_API int prec(InstrumentType);
}