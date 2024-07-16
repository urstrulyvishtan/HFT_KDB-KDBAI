class KDBConnection{
    public:
        KDBConnection(const std::string& host, int port);
        ~KDBConnection();
        void insertMarketData(const std::string& symbol, const std::vector<MarketData>& data);
        std::vector<MarketData> queryMarketData(const std::string& symbol, const std::string& startTime, const std::string& endTime);
    private:
        int handle;
};