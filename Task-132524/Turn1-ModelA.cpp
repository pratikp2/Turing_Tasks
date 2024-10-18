#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <atomic>
#include <shared_mutex>

// Sample GraphDatabaseClient class for demonstration purposes
class GraphDatabaseClient {
public:
  // Simulate fetching user data from the graph database
  std::vector<std::string> getUserData(const std::string& userId) {
    // Delay for simulation
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return {userId, "Some user data", "More user data"};
  }
};

class SessionManager {
public:
  using UserData = std::vector<std::string>;

private:
  GraphDatabaseClient dbClient;
  std::unordered_map<std::string, UserData> sessionDataCache;
  std::shared_mutex cacheMutex;
  std::atomic<bool> cacheInitialized{false};

public:
  SessionManager() = default;

  // Initialize the cache with data for all users
  void initializeCache() {
    // Simulate fetching user IDs from the database
    std::vector<std::string> userIds = {"user1", "user2", "user3", /* ... */};

    for (const std::string& userId : userIds) {
      fetchUserDataAndCache(userId);
    }
    cacheInitialized.store(true);
  }

  // Get user data from the cache, fetching it from the database if necessary
  UserData getUserData(const std::string& sessionId) {
    std::shared_lock lock(cacheMutex);

    const auto it = sessionDataCache.find(sessionId);
    if (it != sessionDataCache.end()) {
      return it->second;
    }

    // User data not in cache, fetch it and cache it
    return fetchUserDataAndCache(sessionId);
  }

private:
  UserData fetchUserDataAndCache(const std::string& userId) {
    std::unique_lock lock(cacheMutex);

    UserData data = dbClient.getUserData(userId);
    sessionDataCache[userId] = data;
    return data;
  }

  bool isCacheInitialized() const {
    return cacheInitialized.load();
  }
};

int main() {
  SessionManager sessionManager;

  // Initialize the cache with data for all users
  if (!sessionManager.isCacheInitialized()) {
    sessionManager.initializeCache();
  }

  // Simulate multiple client requests
  const std::vector<std::string> sessionIds = {"user1", "user2", "user3", "user1", "user4"};

  for (const std::string& sessionId : sessionIds) {
    auto userData = sessionManager.getUserData(sessionId);

    std::cout << "Session ID: " << sessionId << "\n";
    std::cout << "User Data: " << std::endl;
    for (const std::string& field : userData) {
      std::cout << "  " << field << std::endl;
    }
    std::cout << std::endl;
  }