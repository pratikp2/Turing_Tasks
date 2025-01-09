#include <iostream>
#include <memory>
#include <chrono>
#include <unordered_map>
#include <string>
#include <unordered_set>

class Shader {
public:
    static std::unordered_set<Shader*> liveShaders;

    Shader(const std::string& name) {
        std::cout << "Shader " << name << " loaded." << std::endl;
        liveShaders.insert(this);
    }

    ~Shader() {
        std::cout << "Shader destroyed." << std::endl;
        liveShaders.erase(this);
    }

    static size_t getLiveShaderCount() {
        return liveShaders.size();
    }

    void use() {
        std::cout << "Using shader." << std::endl;
    }
};

std::unordered_set<Shader*> Shader::liveShaders;

class ResourceManager {
public:
    std::shared_ptr<Shader> loadShader(const std::string& name) {
        // ... (Same code as before)
    }

    void unloadShader(const std::string& name) {
        if (shaders.find(name) != shaders.end()) {
            shaders.erase(name);
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};


int main() {
    ResourceManager resourceManager;

    // Load shaders
    auto startTime = std::chrono::high_resolution_clock::now();
    auto shader1 = resourceManager.loadShader("BasicShader");
    auto shader2 = resourceManager.loadShader("AdvancedShader");

    // Use shaders
    shader1->use();
    shader2->use();

    // Load same shader again
    auto shader3 = resourceManager.loadShader("BasicShader");

    // Unloading (optional)
    resourceManager.unloadShader("BasicShader");

    // Measure performance
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    std::cout << "Live shaders: " << Shader::getLiveShaderCount() << std::endl;

    // Check for memory leaks (using valgrind)
    return 0;
}
