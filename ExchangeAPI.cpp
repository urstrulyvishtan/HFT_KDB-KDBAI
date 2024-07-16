class ExchangeAPI{
    public:
        ExchangeAPI(const std::string& apiKey, const std::string& secretKey);
        std::string getMarketData(const std::string& symbol);
        void placeOrder(const std::string& symbol, const std::string& side, double quantity, double price);
    
    private:
        std::string apiKey;
        std::string secretKey;
        std::string generateSignature(const std::string data);
        std::string sendRequest(const std::string& endpoint, const std::string& params);
};