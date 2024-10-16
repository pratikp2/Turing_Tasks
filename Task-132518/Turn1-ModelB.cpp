#include <iostream>
#include <vector>
#include <algorithm>

class LoadBalancer {
    private:
        std::vector<std::string> servers;
        int current_server_index = 0;

    public:
        LoadBalancer(const std::vector<std::string>& servers) : servers(servers) {
            // Shuffle the servers to distribute the load initially
            std::shuffle(servers.begin(), servers.end(), std::random_device());
        }

        std::string getNextServer() {
            // Get the server at the current index and then increment the index
            std::string next_server = servers[current_server_index];
            current_server_index = (current_server_index + 1) % servers.size();
            return next_server;
        }

        void addServer(const std::string& server) {
            servers.push_back(server);
        }

        void removeServer(const std::string& server) {
            servers.erase(std::remove(servers.begin(), servers.end(), server), servers.end());
        }
};

int main() {
    // Define the list of servers
    std::vector<std::string> servers = {"server1.example.com", "server2.example.com", "server3.example.com"};

    // Create a load balancer instance
    LoadBalancer load_balancer(servers);

    // Simulate client requests and get the assigned servers
    for (int i = 0; i < 10; ++i) {
        std::string assigned_server = load_balancer.getNextServer();
        std::cout << "Request " << i + 1 << ": Assigned server - " << assigned_server << std::endl;
    }

    // Add a new server
    load_balancer.addServer("server4.example.com");
    std::cout << "Server added: server4.example.com" << std::endl;

    // Remove an existing server
    load_balancer.removeServer("server2.example.com");
    std::cout << "Server removed: server2.example.com" << std::endl;

    return 0;
}