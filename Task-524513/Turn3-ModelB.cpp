#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <stdexcept>

class ResourceLoader {
public:
    // Loads a texture from the specified file path and returns a shared pointer to it.
    // The texture is cached for future reuse.
    inline std::shared_ptr<Texture> loadTexture(const std::string& filePath);

private:
    // A hash map to cache loaded textures
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;

    // Helper function to load a texture from file (actual implementation hidden)
    std::shared_ptr<Texture> loadTextureFromFile(const std::string& filePath);
};

// Simple Texture class for demonstration purposes (implementation details not shown)
class Texture {
public:
    Texture(const std::string& path) : filePath(path) {}
    
    const std::string& getFilePath() const { return filePath; }

private:
    std::string filePath;
};

// Inline function to load a texture
inline std::shared_ptr<Texture> ResourceLoader::loadTexture(const std::string& filePath) {
    // Check if the texture has already been loaded and cached
    auto cacheIt = textureCache.find(filePath);
    if (cacheIt != textureCache.end()) {
        return cacheIt->second;
    }

    // If not cached, load the texture and store it in the cache
    std::shared_ptr<Texture> newTexture = loadTextureFromFile(filePath);
    textureCache[filePath] = newTexture;
    return newTexture;
}

// Helper function to load a texture from file (mocked implementation for demonstration)
std::shared_ptr<Texture> ResourceLoader::loadTextureFromFile(const std::string& filePath) {
    try {
        // Simulate loading the texture
        std::cout << "Loading texture from file: " << filePath << std::endl;
        return std::make_shared<Texture>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading texture '" << filePath << "': " << e.what() << std::endl;
        return nullptr;
    }
}


int main() {
    ResourceLoader resourceLoader;

    // Load the same texture multiple times to demonstrate caching
    auto texture1 = resourceLoader.loadTexture("path/to/texture1.png");
    auto texture2 = resourceLoader.loadTexture("path/to/texture1.png");
    auto texture3 = resourceLoader.loadTexture("path/to/texture2.png");

    return 0;
}
