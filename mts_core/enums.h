#pragma once
#include "mts_core_api.h"
#include "base/MtsType.h"
#incldue "const.h"

namespace mts{
#define FEEDS_TYPE(declare)\
        declare(FT_TICKS, "TICKS", "fmd")\
        declare(FT_BARS, "BARS", "bkd")

        enum FeedsType{ FEEDS_TYPE (SELECT_1_AND_COMMA_IN_3) FT_MAX};
        MTS_CORE_API const char* feedsTypeName(FeedsType type);
        MTS_CORE_API const char* feedsTypeDirName(FeedsType type);
        MTS_CORE_API FeedsType feedsType(const char* type);

#define ENVIRONMENT_MODE(declare)\
        declare(ENVIR_UNKOWN, "UNKOWN", "Invalid")\
        declare(ENVIR_SIMU, "SIMU", "SimulationSimu")\
        declare(ENVIR_BETA, "BETA", "SimulationBeta")\
        declare(ENVIR_REAL, "REAL", "RealTrading")

        enum EnvironmentMode { ENVIRONMENT_MODE(SELECT_1_AND_COMMA_IN_3) ENVIR_MAX};
        MTS_CORE_API const char* environmentModeName(EnvironmentMode mode);
        MTS_CORE_API const char* environmentModeDescription(EnvironmentMode mode);
        MTS_CORE_API EnvironmentMode environmentMode(const char* environmentModeName);
        
#define EXCH_ID_ENUM(declare)\
        declare(EXCH_UNKOWN, "UNKOWN", "--", "Invalid Exchange ID") \
        declare(EXCH_SHSE, "SHSE", "SH", "Shanghai Stock Exchange") \
        declare(EXCH_SZSE, "SZSE", "SZ", "Shenzhen Stock Exchange") \
        declare(EXCH_SHFE, "SHFE", "SC", "Shanghai Futures Exchange") \
        declare(EXCH_DCE, "DCE", "DC", "Dalian Commodity Exchange") \
        declare(EXCH_CZCE, "CZCE", "ZC", "Zhengzhou Commodity Exchange") \
        declare(EXCH_CFFEX, "CFFEX", "SF", "China Financial Futures Exchange") \
        declare(EXCH_INE, "INE", "IN", "China Energy Exchange") \
        declare(EXCH_HB, "HB", "HB", "Huboi") \
        declare(EXCH_HBFUT, "HBFUT", "HBFUT", "Huobi Futures")\
        declare(EXCH_OK, "OK", "OK", "OKEX")\
        declare(EXCH_OKFUT, "OKFUT", "OKFUT", "OKEX Contract")\
        declare(EXCH_OKSWAP, "OKSWAP", "OKSWAP", "OKEX Perpetual Contract")\
        declare(EXCH_BMEX, "BMEX", "BMEX", "BitMEX")\
        declare(EXCH_NYSE, "NYSE", "NY", "New York Stock Exchange") \
        declare(EXCH_NASDAQ, "NASDAQ", "NA", "NASDAQ") \
        declare(EXCH_CME, "CME", "CME", "Chicago Mercantile Exchange") \
        declare(EXCH_CBOE, "CBOE", "CBOE", "Chicago Board Options Exchange") \
        declare(EXCH_LSE, "LSE", "LSE", "London Stock Exchange") \
        declare(EXCH_BSE, "BSE", "BSE", "Bombay Stock Exchange") \
        declare(EXCH_NSE, "NSE", "NSE", "National Stock Exchange of India") \
        declare(EXCH_KRX, "KRX", "KRX", "Korea Exchange") \
        declare(EXCH_TSE, "TSE", "TSE", "Tokyo Stock Exchange") \
        declare(EXCH_HKEX, "HKEX", "HKEX", "Hong Kong Stock Exchange") \
        declare(EXCH_MSE, "MSE", "MSE", "Malta Stock Exchange") \
        declare(EXCH_MX, "MX", "MX", "Mexican Stock Exchange") \
        declare(EXCH_BM, "BM", "BM", "Bermuda Stock Exchange") 

        enum ExchId { EXCH_ID_ENUM(SELECT_1_AND_COMMA_IN_4) EXCH_MAX};
        MTS_CORE_API const char* exchIdName(ExchId exch);
        MTS_CORE_API const char* exchIdShortName(ExchId exch);
        MTS_CORE_API const char* exchIdDescription(ExchId exch);
        MTS_CORE_API ExchId exchId(const char* exchIdName);
        MTS_CORE_API ExchId exchIdFromShort(const char* exchIdShortName);
        MTS_CORE_API bool exchHasBothPos(ExchId);

#define PRICE_TYPE_ENUM(declare)\
        declare(PRICE_UNKOWN, "UNKOWN", "INVALID")\
        declare(PRICE_LIMIT, "limit", "Price Limit")\
        declare(PRICE_MKT, "market", "Price Market")\
        declare(PRICE_LIMIT_MAKER, "limit_maker", "Limit Price Market Making")\
        declare(PRICE_IOC, "IOC", "IOC")

        enum PriceType {PRICE_TYPE_ENUM(SELECT_1_AND_COMMA_IN_3) PRICE_TYPE_MAX};

        MTS_CORE_API const char* priceTypeName(PriceType);
        MTS_CORE_API PriceType priceType(const char*);
        MTS_CORE_API const char* priceTypeDescription(PriceType);

#define DIRECTION_SIDE_ENUM(declare) \
        declare(D_UNKOWN, "UNKOWN", "Invalid transaction type") \
        declare(D_BUY, "BUY", "Buy") \
        declare(D_SELL, "SELL", "Sell") \
        declare(D_SHORT, "SHORT", "Short") \
        declare(D_COVER, "COVER", "Cover")

        enum DirectionSide { DIRECTION_SIDE_ENUM(SELECT_1_AND_COMMA_IN_3) DIRECTION_SIDE_MAX};

        MTS_CORE_API const char* directionSideName(DirectionSide);
        MTS_CORE_API DirectionSide directionSide(const char*);
        MTS_CORE_API const char* directionSideDescription(DirectionSide);

#define TIME_CONDITION_ENUM(declare)\
        declare(TC_UNKOWN, "UNKOWN", "Invalid validity period") \
        declare(TC_IOC, "ioc", "Complete immediately or cancel") \
        declare(TC_GFS, "gfs", "Good for Session") \
        declare(TC_GTC, "gtc", "Good till canceled") \
        declare(TC_GFD, "gfd", "Good for day") \
        declare(TC_GTD, "gtd", "Good till date")\
        declare(TC_GFA, "gfa", "Good for Auction")

        enum TimeCondition { TIME_CONDITION_ENUM(SELECT_1_AND_COMMA_IN_3) TIME_CONDITION_MAX};

        MTS_CORE_API const char* timeConditionName(TimeCondition);
        MTS_CORE_API TimeCondition timeCondition(const char*);
        MTS_CORE_API const char* timeConditionDescription(TimeCondition);

#define COMBOFFSETFLAG_ENUM(declare)\
        declare(OF_UNKOWN, "UNKOWN", "Invalid transaction type") \
        declare(OF_OPEN, "OPEN", "Open") \
        declare(OF_CLOSE, "CLOSE", "Close") \
        declare(OF_FORCECLOSE, "forceclose", "Forced Liquidation")\
        declare(OF_CLOSEYESTERDAY, "closeyesterday", "Close Yesterday")\
        declare(OF_CLOSETODAY, "closetoday", "Close Today")

        enum ComboOffsetFlag { COMBOFFSETFLAG_ENUM(SELECT_1_AND_COMMA_IN_3) COMBOFFSETFLAG_MAX};

        MTS_CORE_API const char* combOffsetFlagName(CombOffsetFlag);
        MTS_CORE_API CombOffsetFlag combOffsetFlag(const char*);
        MTS_CORE_API const char* combOffsetFlagDescription(CombOffsetFlag);

#define FRONT_PROTOCOL_ENUM(declare) \
        declare(FP_UNKOWN, "UNKOWN", "Invalid transaction type") \
        declare(FP_CTP, "CTP", "CTP") \
        declare(FP_TDF, "TDF", "TDF") \
        declare(FP_IB, "IB", "IB") \
        declare(FP_OK, "OK", "OK") \
        declare(FP_OKFUT, "OKFUT", "OKEX_FUT") \
        declare(FP_OKSWAP, "OKSWAP", "OKEX_SWAP") \
        declare(FP_BMEX, "BMEX", "BitMEX") \
        declare(FP_NYSE, "NYSE", "New York Stock Exchange") \
        declare(FP_NASDAQ, "NASDAQ", "NASDAQ") \
        declare(FP_CME, "CME", "Chicago Mercantile Exchange") \
        declare(FP_CBOE, "CBOE", "Chicago Board Options Exchange") \
        declare(FP_LSE, "LSE", "London Stock Exchange") \
        declare(FP_BSE, "BSE", "Bombay Stock Exchange") \
        declare(FP_NSE, "NSE", "National Stock Exchange of India") \
        declare(FP_KRX, "KRX", "Korea Exchange") \
        declare(FP_TSE, "TSE", "Tokyo Stock Exchange") \
        declare(FP_HKEX, "HKEX", "Hong Kong Stock Exchange") \
        declare(FP_MSE, "MSE", "Malta Stock Exchange") \
        declare(FP_MX, "MX", "Mexican Stock Exchange") \
        declare(FP_BM, "BM", "Bermuda Stock Exchange")

        enum FrontProtocol {FRONT_PROTOCOL_ENUM (SELECT_1_AND_COMMA_IN_3) FRONT_PROTOCOL_MAX};
        MTS_CORE_API const char* frontProtocolName(FrontProtocol);
        MTS_CORE_API FrontProtocol frontProtocol(const char*);
        MTS_CORE_API const char* frontProtocolDescription(FrontProtocol);

        enum OrderStatus{
            OS_NULL = 0x0000,
            OS_NEW_REQUEST = 0x0001,
            OS_NEW_DONE = 0x0002,
            OS_NEW_REJECT = 0x0004,
            OS_FILL = 0x0008,
            OS_CANCEL_REQUEST = 0x0010,
            OS_CANCEL_DONE = 0x0020,
            OS_CANCEL_REJECT = 0x0040,
            OS_ORDER_DONE = 0x0080,
            OS_ALL_FILL - OS_ORDER_DONE
        };

        enum OrderReportType{
            ORT_UNKOWN,
            ORT_NEW_REQUEST,
            ORT_NEW_DONE,
            ORT_NEW_REJECT,
            ORT_FILL,
            ORT_CANCEL_REQUEST,
            ORT_CANCEL_DONE,
            ORT_CANCEL_REJECT,
            ORT_ORDER_DONE,
            ORT_ORDER
        };

#define API_TYPE_ENUM(declare)\
        declare(API_UNKOWN, "UNKOWN", "Invalid API") \
        declare(API_CTP, "CTP", "CTP") 

        enum ApiType {API_TYPE_ENUM(SELECT_1_AND_COMMA_IN_3) API_NAX};

        MTS_CORE_API const char* apiTypenName(ApiType);
        MTS_CORE_API ApiType apiType(const char*);
        MTS_CORE_API const char* apiTypeDescription(ApiType);
    
#define INSTRUMENT_KIND_ENUM(declare)\
        declare(KIND_NORMAL, "NORMAL", "Normal Contract") \
        declare(KIND_SERIES, "SERIES", "Continous Contract")

        enum InstrumentKind { INSTRUMENT_KIND_ENUM(SELECT_1_AND_COMMA_IN_3) INSTRUMENT_KIND_MAX};

        MTS_CORE_API const char* instrumentKindName(InstrumentKind);
        MTS_CORE_API InstrumentKind instrumentKind(const char*);
        MTS_CORE_API const char* instrumentKindDescription(InstrumentKind);

#define ALGO_STATUS_ENUM(declare) \
        declare(ALGO_STATUS_NONE, "none", "initial") \
        declare(ALGO_STATUS_RUNNING, "running", "running") \
        declare(ALGO_STATUS_STOP, "stop", "stop") \
        declare(ALGO_STATUS_CANCELED, "canceled", "canceled") \
        declare(ALGO_STATUS_DELETED, "deleted", "deleted") \
        declare(ALGO_STATUS_FINISHED, "finished", "finished")

        enum AlgoStatus { ALGO_STATUS_ENUM(SELECT_1_AND_COMMA_IN_3) ALGO_STATUS_MAX};

        MTS_CORE_API const char* algoStatusName(AlgoStatus);
        MTS_CORE_API AlgoStatus algoStatus(const char*);   
        MTS_CORE_API const char* algoStatusDescription(AlgoStatus);

#define ALGO_TYPE_ENUM(declare) \
        declare(ALGO_NONE, "none", "none") \
        declare(ALGO_TIME_SLICE, "timeslice", "time slice polling") \
        declare(ALGO_VOLUME_WEIDGH, "vwap", "Volume Weighted Average Price")
        declare(ALGO_TIME_WEIDGH, "twap", "Time Weighted Average Price")

        enum AlgoType { ALGO_TYPE_ENUM(SELECT_1_AND_COMMA_IN_3) ALGO_TYPE_MAX};

        MTS_CORE_API const char* algoTypeName(AlgoType);
        MTS_CORE_API AlgoType algoType(const char*);
        MTS_CORE_API const char* algoTypeDescription(AlgoType);
        MTS_CORE_API AlgoType algoDescription2Type(const char*);

#define MTS_COMPONENT_ENUM(declare)\
        declare(MTS_COMP_CLOCK, "clock", "Clock") \
        declare(MTS_COMP_FEEDS, "feeds", "Feeds") \
        declare(MTS_COMP_TRADE, "trade", "Trade")

        enum MtsComponent { MTS_COMPONENT_ENUM(SELECT_1_AND_COMMA_IN_3) MTS_COMP_MAX};
        MTS_CORE_API const char* mtsComponentName(MtsComponent);
        MTS_CORE_API MtsComponent mtsComponent(const char*);
        MTS_CORE_API const char* mtsComponentDescription(MtsComponent);

}