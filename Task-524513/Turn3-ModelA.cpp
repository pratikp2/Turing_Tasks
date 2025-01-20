#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <stdexcept>

// Forward declaration for Texture class
class Texture {
public:
    explicit Texture(const std::string& filePath) {
        // Simulate loading the texture from a file
        std::cout << "Loading texture from: " << filePath << std::endl;
    }
};

// ResourceLoader class for managing loaded textures
class ResourceLoader {
public:
    // Inline function to access the loader (get cached texture or load new one)
    inline std::shared_ptr<Texture> LoadTexture(const std::string& filePath);

private:
    // Cache for loaded textures
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;

    // Actual texture loading implementation
    std::shared_ptr<Texture> LoadTextureFromFile(const std::string& filePath);
};

#endif // RESOURCE_LOADER_H

// Inline function to load or retrieve a cached texture
inline std::shared_ptr<Texture> ResourceLoader::LoadTexture(const std::string& filePath) {
    // Check if the texture is already cached
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        // Texture found in cache, returning cached pointer
        return it->second;
    }

    // If not cached, load the texture
    auto texture = LoadTextureFromFile(filePath);
    if (texture) {
        // Store loaded texture in cache
        textureCache[filePath] = texture;
    }
    return texture;
}

// Implementation of the actual texture loading process
std::shared_ptr<Texture> ResourceLoader::LoadTextureFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Texture>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading texture from " << filePath << ": " << e.what() << std::endl;
        return nullptr; // Handle failed texture loading gracefully
    }
}

int main() {
    ResourceLoader resourceLoader;

    // Load a texture
    auto texture1 = resourceLoader.LoadTexture("assets/textures/texture1.png");
    
    // Load another texture
    auto texture2 = resourceLoader.LoadTexture("assets/textures/texture2.png");

    // Load the same texture again to demonstrate caching
    auto texture3 = resourceLoader.LoadTexture("assets/textures/texture1.png");
    
    // Verify that it's the same cached texture
    if (texture1 == texture3) {
        std::cout << "Successfully reused cached texture1." << std::endl;
    } else {
        std::cout << "Texture reloaded instead of using cache." << std::endl;
    }
    
    return 0;
}
