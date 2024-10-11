#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>

// Sample Server class
class Server {
public:
  std::string name;
  bool is_primary;
  std::atomic<bool> is_active{true};

  Server(std::string name, bool is_primary) : name(name), is_primary(is_primary) {}

  void handleRequest() {
    while (is_active.load()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Handling request on " << name << std::endl;
    }
  }

  void setActive(bool active) {
    is_active.store(active);
  }
};

// Client class
class Client {
public:
  std::vector<Server*> servers;
  int current_server_index;

  Client(std::vector<Server*> servers) : servers(servers), current_server_index(0) {}

  void sendRequest() {
    while (true) {
      if (!servers[current_server_index]->is_active.load()) {
        failover();
      }

      std::cout << "Sending request to " << servers[current_server_index]->name << std::endl;
      servers[current_server_index]->handleRequest();
    }
  }

private:
  void failover() {
    std::cout << "Failing over to a backup server..." << std::endl;

    // Simple round-robin failover strategy
    current_server_index = (current_server_index + 1) % servers.size();
  }
};

int main() {
  Server server1("Server1", true);
  Server server2("Server2", false);

  std::vector<Server*> servers = {&server1, &server2};

  Client client(servers);

  std::thread server1_thread(&Server::handleRequest, &server1);
  std::thread server2_thread(&Server::handleRequest, &server2);
  std::thread client_thread(&Client::sendRequest, &client);

  // Simulate a scenario where Server1 fails
  std::this_thread::sleep_for(std::chrono::seconds(5));
  server1.setActive(false);

  client_thread.join();
  server1_thread.join();
  server2_thread.join();
  return 0;
}
