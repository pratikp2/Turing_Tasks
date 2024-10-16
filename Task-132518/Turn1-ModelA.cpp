#include <iostream>
#include <vector>
#include <string>
#include <atomic>

class LoadBalancer {
private:
  std::vector<std::string> backendServers;
  std::atomic<size_t> nextServerIndex{0};

public:
  LoadBalancer(const std::vector<std::string>& servers) : backendServers(servers) {
    if (backendServers.empty()) {
      throw std::runtime_error("No backend servers provided.");
    }
  }

  std::string getNextBackendServer() {
    size_t currentIndex = nextServerIndex.fetch_add(1, std::memory_order_relaxed) % backendServers.size();
    return backendServers[currentIndex];
  }

  void addBackendServer(const std::string& server) {
    backendServers.push_back(server);
  }

  size_t getBackendServerCount() const {
    return backendServers.size();
  }
};

int main() {
  // Example backend servers
  std::vector<std::string> backendServers = {"server1.example.com", "server2.example.com", "server3.example.com"};

  LoadBalancer balancer(backendServers);

  std::cout << "Load Balancer Initialized with " << balancer.getBackendServerCount() << " servers:" << std::endl;
  for (const std::string& server : backendServers) {
    std::cout << " - " << server << std::endl;
  }

  // Simulate client requests and distribute them to backend servers
  for (int i = 0; i < 10; ++i) {
    std::string selectedServer = balancer.getNextBackendServer();
    std::cout << "Handling request " << i << " to: " << selectedServer << std::endl;
  }

  return 0;
}
