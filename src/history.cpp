#include <map>
#include <vector>
#include <string>

// ChatGPTed

class History {
    
private:
    std::string symbol;
    std::vector<float> history;

public:
    static std::map<std::string, History> histories;

    History(std::string symbol, std::vector<float> history)
        : symbol(symbol), history(history) 
    {
        histories[symbol] = *this;
    }

    void initialiseHistory() {
        history = {1.2f, 3.4f, 5.6f};
    }

    std::vector<float> getHistory() {
        return history;
    }

    static History& findBySymbol(const std::string& symbol) {
        return histories.at(symbol);
    }
};

std::map<std::string, History> History::histories = {};
