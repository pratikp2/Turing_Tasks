#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <stdexcept>

// Forward declarations for Texture and Model classes
class Texture;
class Model;

class ResourceManager {
public:
    // Load a texture and return a pointer to it
    inline std::shared_ptr<Texture> LoadTexture(const std::string& filePath);
    
    // Load a model and return a pointer to it
    inline std::shared_ptr<Model> LoadModel(const std::string& filePath);

private:
    // Hash maps to cache loaded resources
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;
    std::unordered_map<std::string, std::shared_ptr<Model>> modelCache;

    // Helper functions to actually load resources
    std::shared_ptr<Texture> LoadTextureFromFile(const std::string& filePath);
    std::shared_ptr<Model> LoadModelFromFile(const std::string& filePath);
};

// Assuming Texture and Model classes are defined elsewhere
class Texture {
public:
    Texture(const std::string& path) { /* Load texture from file */ }
};

class Model {
public:
    Model(const std::string& path) { /* Load model from file */ }
};

// Inline function to load a texture
inline std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& filePath) {
    // Check if the texture is already cached
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    // If not cached, load the texture and cache it
    auto texture = LoadTextureFromFile(filePath);
    textureCache[filePath] = texture;
    return texture;
}

// Inline function to load a model
inline std::shared_ptr<Model> ResourceManager::LoadModel(const std::string& filePath) {
    // Check if the model is already cached
    auto it = modelCache.find(filePath);
    if (it != modelCache.end()) {
        return it->second;
    }

    // If not cached, load the model and cache it
    auto model = LoadModelFromFile(filePath);
    modelCache[filePath] = model;
    return model;
}

// Actual file loading implementation (could involve actual file I/O)
std::shared_ptr<Texture> ResourceManager::LoadTextureFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Texture>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading texture: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<Model> ResourceManager::LoadModelFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Model>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading model: " << e.what() << std::endl;
        return nullptr;
    }
}

int main() {
    ResourceManager resourceManager;

    // Load textures and models
    auto texture1 = resourceManager.LoadTexture("path/to/texture1.png");
    auto model1 = resourceManager.LoadModel("path/to/model1.obj");

    // Subsequent calls will retrieve the cached versions
    auto texture2 = resourceManager.LoadTexture("path/to/texture1.png");
    auto model2 = resourceManager.LoadModel("path/to/model1.obj");

    return 0;
}
