#ifndef __Currency_H__
#define __Currency_H__
#pragma once

#include "base_api.h"
#include "enum_txt.h"

#define CURRENCY_ID_ENUM(declare)\
        declare(CURRENCY_UNKNOWN, "UNKNOWN", "UNKNOWN")\
        declare(CURRENCY_CNY, "CNY", "RMB")\
        declare(CURRENCY_USD, "USD", "Dollar")\
        declare(CURRENCY_HKD, "HKD", "Hong Kong Dollar")\
        declare(CURRENCY_JPY, "JPY", "Japanese Yen")\
        declare(CURRENCY_EUR, "EUR", "Euro")\
        declare(CURRENCY_GBP, "GBP", "Pound Streling")
        declare(CURRENCY_INR, "INR", "Indian Rupees")

enum CurrencyId {CURRENCY_ID_ENUM (SELECT_1_AND_COMMA_IN_3) CURRENCY_MAX};

BASE_API const char* currencyIdName(CurrencyID currency);
BASE_API CurrencyId currencyId(const char* currencyName);

#endif // __Currency_H__