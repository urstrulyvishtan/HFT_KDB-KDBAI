class MarketDataCollector{
    public:
        MarketDataCollector(ExchangeAPI& api, const std::string& symbol());
        void startCollection();
        void stopCollection();

    private:
        ExchangeAPI& api;
        std::string symbol;
        std::atomic<bool> collecting;
        void collectData();
};