#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

class Shader {
public:
    Shader(const std::string& name) {
        std::cout << "Shader " << name << " loaded." << std::endl;
    }
    
    ~Shader() {
        std::cout << "Shader destroyed." << std::endl;
    }
    
    void use() {
        std::cout << "Using shader." << std::endl;
    }
};

class ResourceManager {
public:
    // Load a shader and return a smart pointer to it
    std::shared_ptr<Shader> loadShader(const std::string& name) {
        auto it = shaders.find(name);
        if (it != shaders.end()) {
            return it->second; // Return already loaded shader
        }

        // Create new shader and store it in the map
        auto shader = std::make_shared<Shader>(name);
        shaders[name] = shader;
        return shader;
    }

    // Explicitly unload a shader (optional)
    void unloadShader(const std::string& name) {
        shaders.erase(name);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

int main() {
    ResourceManager resourceManager;

    // Load shaders
    auto shader1 = resourceManager.loadShader("BasicShader");
    auto shader2 = resourceManager.loadShader("AdvancedShader");
    
    // Use shaders
    shader1->use();
    shader2->use();

    // Shader1 is still valid because it is shared
    auto shader3 = resourceManager.loadShader("BasicShader");
    shader3->use();

    // Unloading (optional)
    resourceManager.unloadShader("BasicShader");
    
    // At this point shader2 is still loaded, shader1 and shader3 will be unloaded.
    
    return 0;
}
