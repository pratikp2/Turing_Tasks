#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>

// Simple Shader class
class Shader {
public:
    Shader(const std::string& name) : name(name) {
        std::cout << "Shader " << name << " loaded." << std::endl;
    }
    
    ~Shader() {
        std::cout << "Shader " << name << " destroyed." << std::endl;
    }
    
    void use() {
        std::cout << "Using shader " << name << "." << std::endl;
    }

private:
    std::string name;
};

// Memory tracker to monitor allocations
class MemoryTracker {
public:
    static void allocate(size_t size) {
        currentUsage += size;
        ++allocationCount;
    }

    static void deallocate(size_t size) {
        currentUsage -= size;
        ++deallocationCount;
    }

    static void report() {
        std::cout << "Current Memory Usage: " << currentUsage << " bytes\n";
        std::cout << "Allocations: " << allocationCount << ", Deallocations: " << deallocationCount << std::endl;
    }

private:
    static size_t currentUsage;
    static size_t allocationCount;
    static size_t deallocationCount;
};

// Initialize static members
size_t MemoryTracker::currentUsage = 0;
size_t MemoryTracker::allocationCount = 0;
size_t MemoryTracker::deallocationCount = 0;

class ResourceManager {
public:
    std::shared_ptr<Shader> loadShader(const std::string& name) {
        auto it = shaders.find(name);
        if (it != shaders.end()) {
            return it->second; // Return already loaded shader
        }

        // Create new shader and store it in the map
        auto shader = std::shared_ptr<Shader>(new Shader(name), [](Shader* s) {
            MemoryTracker::deallocate(sizeof(Shader));
            delete s;
        });

        MemoryTracker::allocate(sizeof(Shader));
        shaders[name] = shader;
        return shader;
    }

    void unloadShader(const std::string& name) {
        shaders.erase(name);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

// Timing utility
class Timer {
public:
    Timer(const std::string& name) : name(name), start(std::chrono::high_resolution_clock::now()) {}
    
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Execution time for " << name << ": " << duration.count() << " ms\n";
    }

private:
    std::string name;
};

int main() {
    {
        ResourceManager resourceManager;

        {
            Timer loadTimer("Shader Loading");
            // Load shaders
            auto shader1 = resourceManager.loadShader("BasicShader");
            auto shader2 = resourceManager.loadShader("AdvancedShader");
        
            // Use shaders
            shader1->use();
            shader2->use();
        } // Timer automatically stops here

        MemoryTracker::report();

        // Unloading (optional)
        resourceManager.unloadShader("BasicShader");
        resourceManager.unloadShader("AdvancedShader");
    } // ResourceManager goes out of scope, automatic cleanup occurs

    MemoryTracker::report();

    return 0;
}
