struct MarketData{
    std::chrono::time_point<std::chrono::system_clock> time;
    double price;
    double size;
};