#ifndef __Currency_H__
#define __Currency_H__
#pragma once

#include "base_api.h"
#include "enum_txt.h"

#define CURRENCY_ID_ENUM(declare)\
        declare(CURRENCY_UNKNOWN, "UNKNOWN")\
        declare(CURRENCY_CNY, "CNY")\
        declare(CURRENCY_USD, "USD")\
        declare(CURRENCY_HKD, "HKD")\
        declare(CURRENCY_JPY, "JPY")\
        declare(CURRENCY_EUR, "EUR")\
        declare(CURRENCY_GBP, "GBP")
        declare(CURRENCY_INR, "INR")

enum CurrencyId {CURRENCY_ID_ENUM (SELECT_1_AND_COMMA_IN_3) CURRENCY_MAX};

BASE_API const char* currencyIdName(CurrencyID currency);
BASE_API CurrencyId currencyId(const char* currencyName);

#endif // __Currency_H__