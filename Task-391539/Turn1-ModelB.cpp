#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Forward declarations
class DatabaseCache;
class BaseDatabaseCacheLogger;
class NullDatabaseCacheLogger : public BaseDatabaseCacheLogger;
class ConsoleDatabaseCacheLogger : public BaseDatabaseCacheLogger;

//Component Class : Database Cache
class DatabaseCache {
private:
    std::string name_;
protected:
    std::shared_ptr<BaseDatabaseCacheLogger> logger_;

public:
    DatabaseCache(const std::string& name, std::shared_ptr<BaseDatabaseCacheLogger> logger = std::make_shared<NullDatabaseCacheLogger>())
        : name_(name), logger_(logger) { }
    virtual void insert(const std::string& key, const std::string& value) {
        logger_->logInsert(name_, key, value);
    }
    virtual std::string get(const std::string& key) const {
        logger_->logGet(name_, key);
        return ""; // Provide real implementation in derived classes
    }

    virtual void remove(const std::string& key) {
        logger_->logRemove(name_, key);
    }
     virtual ~DatabaseCache() = default;
};

//Middleware : Database Cache Medaitor
class DatabaseCacheMediator {
private:
    std::vector<std::shared_ptr<DatabaseCache>> caches_;

public:
    void registerDatabaseCache(std::shared_ptr<DatabaseCache> cache) {
        caches_.push_back(cache);
    }

    void insert(const std::string& cacheName, const std::string& key, const std::string& value) {
        // Assume cacheName is unique
        for (const auto& cache : caches_) {
            if (cache->name_ == cacheName) {
                cache->insert(key, value);
                break;
            }
        }
    }

    std::string get(const std::string& cacheName, const std::string& key) const {
        // Assume cacheName is unique
        for (const auto& cache : caches_) {
            if (cache->name_ == cacheName) {
                return cache->get(key);
            }
        }
        return ""; // Cache not found
    }

    void remove(const std::string& cacheName, const std::string& key) {
        // Assume cacheName is unique
        for (const auto& cache : caches_) {
            if (cache->name_ == cacheName) {
                cache->remove(key);
                break;
            }
        }
    }
};

//DecorationClass : The base calss for decorating the logging behavior around database actions.
class BaseDatabaseCacheLogger {
public:
    virtual void logInsert(const std::string& cacheName, const std::string& key, const std::string& value) = 0;
    virtual void logGet(const std::string& cacheName, const std::string& key) const = 0;
    virtual void logRemove(const std::string& cacheName, const std::string& key) = 0;
    virtual ~BaseDatabaseCacheLogger() = default;
};

//NullDatabaseCacheLogger Decorator : behaviour choice 1 - Unconditional         Disabled Logging
class NullDatabaseCacheLogger : public BaseDatabaseCacheLogger {
public:
    void logInsert(const std::string&, const std::string&, const std::string&) override {}
    void logGet(const std::string&, const std::string&) const override {}
    void logRemove(const std::string&, const std::string&) override {}
};

//consoleDatabaseCachLogger Decorator : Behaviour choice 2 : Console Centric outcomea are logged.
class ConsoleDatabaseCacheLogger : public BaseDatabaseCacheLogger {
public:
    void logInsert(const std::string& cacheName, const std::string& key, const std::string& value) override {
        std::cout << "Inserted into " << cacheName << ": [" << key << "] -> " << value << std::endl;
    }
    void logGet(const std::string& cacheName, const std::string& key) const override {
        std::cout << "Getting from " << cacheName << ": [" << key << "]" << std::endl;
    }
    void logRemove(const std::string& cacheName, const std::string& key) override {
        std::cout << "Removing from " << cacheName << ": [" << key << "]" << std::endl;
    }
};

//Examples
int main() {
    //Create system
     std::shared_ptr<DatabaseCacheMediator> mediator = std::make_shared<DatabaseCacheMediator>();

    //Creating / Decocorating cacheComponent instances |AND| Associates with Meditiaor 
  
    { //\{
        // Create a cache with default (no) logging
        std::shared_ptr<DatabaseCache> defaultCache = std::make_shared<DatabaseCache>("DefaultCache");
        mediator->registerDatabaseCache(defaultCache);
        //Reshaping cache behaviour
        defaultCache->logger_ = std::make_shared<ConsoleDatabaseCacheLogger>();

        // Interact with cache via mediator
        mediator->insert("DefaultCache", "userId", "123");
        mediator->get("DefaultCache", "userId");
        mediator->remove("DefaultCache", "userId");
    }//\}

     { //\{
         //Decorator} You can specify glue on helper object construction
         std::shared_ptr<DatabaseCache> segmentedConsoleLogger = std::make_shared<DatabaseCache>(
                                                            "SegmentedConsoleLogger",
                                                            std::make_shared<ConsoleDatabaseCacheLogger>()
                                                    );

        mediator->registerDatabaseCache(segmentedConsoleLogger);
  
  
        //Use temediator to tentacted the state of the auxilary cache oggetto.  
         mediator->insert("SegmentedConsoleLogger", "favoriteNumber","999");
         mediator->remove("SegmentedConsoleLogger", "nonExistantEntry");        
     }//\}
    //So at this stage, the system ,trigger actions use mediatior, are transpoter mediated 
    std::cout << "Program End." << std::endl;

    return 0;
}
