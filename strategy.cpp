class Strategy{
    public:
        virtual ~Strategy() = default;
        virtual void onMarketData(const MarketData& data) = 0;
        virtual void onOrderUpdate(const OrderUpdate& update) = 0;
};