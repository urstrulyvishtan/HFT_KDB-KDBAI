#pragma once

#ifdef _WIN32
#include "../../api/win64/CTP/ThostFtdcUserApiDataType.h"
#else
#include "../../api/linux64/CTP/ThostFtdcUserApiDataType.h"
#include <float.h>
#endif

#define SIMU_FEEDS_FILE_EXTNAME ".fmd"

#define INSTRUMENT_DB_FILE "instrument_db.json"
#define CONTINOUS_CONTRACT_FILE "continous_contract.json"
#define RISK_SETTING_FILE "risk_setting.json"

#define STREGETY_NAME "stregety_name"
#define STREGETY_LANGUAGE "stregety_language"

#define SYMBOL_FIELD "symbol"

#define ORDER_SYMBOL SYMBOL_FIELD
#define ORDER_PRICE "price"
#define ORDER_VOLUME "volume"
#define ORDER_DIRECTION "direction"
#define ORDER_ID "orderId"
#define ORDER_LEFT_VOLUME "leftVolume"
#define ORDER_FILL_VOLUME "fillVolume"
#define ORDER_SEND_TIME "sendTime"
#define ORDER_UPDATE_TIME "updateTime"
#define ORDER_STATUS "orderStatus"
#define ORDER_STATUS_MSG "statusMsg"

#define FILL_ID "fillId"

#define ERROR_ID "errorId"
#define ERROR_MSG "errorMsg"
#define ERROR_LEVEL "errorLevel"

#define POSITION_DIRECTION ORDER_DIRECTION
#define POSITION_POSITION "position"
#define POSITION_COMMISSION "commission"
#define POSITION_MARGIN "margin"
#define POSITION_DATE "date"

#define INSTRUMENT_SYMBOL SYMBOL_FIELD
#define INSTRUMENT_PRICE_TICK "priceTick"
#define INSTRUMENT_VOLUME_MULTIPLE "volumeMultiple"

#define ACCOUNT_POSITION "positions"
#define ACCOUNT_ORDERS "orders"
#define ACCOUNT_FILLS "fills"
#define ACCOUNT_INSTRUMENTS "instruments"

#define ALGO_NAMES "algo_names"
#define MONITOR_STRATEGYID_DEFAULT 9
#define ALGO_STRATEGYID_DEFAULT 8

#define QUOTE_DEPTH 25

enum OwnerLevel{
    OL_FRONT,
    OL_EXCH
};

enum PositionDirection{
    PD_NET = THOST_FTDC_PD_Net,
    PD_LONG = THOST_FTDC_PD_Long,
    PD_SHORT = THOST_FTDC_PD_Short
};

enum GetMode{
    GM_GET,
    GM_GET_OR_CREATE
};

enum OrderActionStatus{
    OAS_READY,
    OAS_SENT,
    OAS_DONE,
    OAS_REJECT
};

#define CONTINOUS_CONTRACT_SUFFIX "888"

#define DEFAULT_STRATEGY_ID 0