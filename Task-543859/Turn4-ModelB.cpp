#include <iostream>
#include <string>
#include <map>
#include <functional>

enum Protocol {
    TCP,
    UDP,
    ICMP,
    UNKNOWN
};

using ProtocolHandler = std::function<void()>;

std::map<Protocol, ProtocolHandler> protocolHandlers = {
    {TCP, handleTCP},
    {UDP, handleUDP},
    {ICMP, handleICMP}
};

Protocol getProtocolFromInput(const std::string& protocolStr) {
    if (protocolStr == "TCP") return TCP;
    else if (protocolStr == "UDP") return UDP;
    else if (protocolStr == "ICMP") return ICMP;
    else return UNKNOWN;
}

void processPacket(const std::string& protocolStr) {
    Protocol protocol = getProtocolFromInput(protocolStr);

    auto handlerIt = protocolHandlers.find(protocol);
    if (handlerIt != protocolHandlers.end()) {
        handlerIt->second();
    } else {
        handleUnknown();
    }
}

int main() {
    std::string protocol;
    std::cout << "Enter the protocol (TCP, UDP, ICMP): ";
    std::cin >> protocol;

    processPacket(protocol);

    return 0;
}
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

enum Protocol {
    TCP,
    UDP,
    ICMP,
    UNKNOWN
};

template<typename Key, typename Value, typename Hash = std::hash<Key>, typename Equal = std::equal_to<Key>, typename Allocator = std::allocator<std::pair<const Key, Value>>>
class constexpr_unordered_map {
private:
    std::unordered_map<Key, Value, Hash, Equal, Allocator> map;

public:
    constexpr constexpr_unordered_map(std::initializer_list<std::pair<const Key, Value>> l) {
        for (const auto& [key, value] : l) {
            map[key] = value;
        }
    }

    constexpr Value operator[](const Key& key) const {
        return map.at(key);
    }
};

using ProtocolHandlersMap = constexpr_unordered_map<std::string_view, void()>;

constexpr ProtocolHandlersMap protocolHandlers = {
    {"TCP", handleTCP},
    {"UDP", handleUDP},
    {"ICMP", handleICMP}
};

Protocol getProtocolFromInput(const std::string& protocolStr) {
    if (protocolStr == "TCP") return TCP;
    else if (protocolStr == "UDP") return UDP;
    else if (protocolStr == "ICMP") return ICMP;
    else return UNKNOWN;
}

void processPacket(const std::string& protocolStr) {
    std::string_view protocolView(protocolStr);

    auto handler = protocolHandlers[protocolView];
    if (handler) {
        handler();
    } else {
        handleUnknown();
    }
}

int main() {
    std::string protocol;
    std::cout << "Enter the protocol (TCP, UDP, ICMP): ";
    std::cin >> protocol;

    processPacket(protocol);

    return 0;
}
