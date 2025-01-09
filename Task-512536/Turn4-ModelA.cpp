#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <fstream> // For file handling

// Custom deleter for file handles
struct FileDeleter {
    void operator()(std::ifstream* file) const {
        if (file) {
            file->close();
            delete file;
            std::cout << "File closed and deleted." << std::endl;
        }
    }
};

// Simple ShaderBuffer class that simulates a dynamically allocated shader buffer
class ShaderBuffer {
public:
    ShaderBuffer(size_t size) : size(size) {
        // Simulate allocation of a buffer
        buffer = new int[size]; // Placeholder for shader data
        std::cout << "ShaderBuffer of size " << size << " allocated." << std::endl;
    }

    ~ShaderBuffer() {
        delete[] buffer; // Clean up the buffer
        std::cout << "ShaderBuffer destroyed." << std::endl;
    }

private:
    int* buffer; // Pointer to the allocated buffer
    size_t size; // Size of the buffer
};

// A mock Shader class simulating a shader
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

class ResourceManager {
public:
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

    std::unique_ptr<ShaderBuffer, std::function<void(ShaderBuffer*)>> createShaderBuffer(size_t size) {
        return std::unique_ptr<ShaderBuffer, std::function<void(ShaderBuffer*)>>(
            new ShaderBuffer(size), [](ShaderBuffer* buffer) {
                delete buffer; // Custom deleter for ShaderBuffer
        });
    }

    std::shared_ptr<std::ifstream> openFile(const std::string& filename) {
        // Using a custom deleter for file handles
        return std::shared_ptr<std::ifstream>(new std::ifstream(filename), FileDeleter{});
    }

    void unloadShader(const std::string& name) {
        shaders.erase(name);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

int main() {
    ResourceManager resourceManager;

    // Load a shader
    auto shader1 = resourceManager.loadShader("BasicShader");
    shader1->use();

    // Create a ShaderBuffer 
    {
        auto shaderBuffer = resourceManager.createShaderBuffer(1024);
        // Use the shader buffer here (this block simulates using it)
    }
    // shaderBuffer will be automatically deleted after this block
     
    // Open a file with a custom deleter
    auto file = resourceManager.openFile("example.txt");
    if (file->is_open()) {
        std::cout << "File opened successfully." << std::endl;
        // Read or write operations here
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }

    // Shader will be automatically deleted when going out of scope
    return 0;
}
