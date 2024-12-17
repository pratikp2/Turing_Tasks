#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

class Texture {
public:
    explicit Texture(const std::string& filename) : filename_(filename) {
        // Simulate loading a texture (in reality, this would load from a file)
        std::cout << "Loading texture from: " << filename << std::endl;
    }
    
    void use() const {
        std::cout << "Using texture: " << filename_ << std::endl;
    }

private:
    std::string filename_;
};

class ResourceManager {
public:
    // Delete copy constructor and assignment operator
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Access the singleton instance
    static ResourceManager& getInstance() {
        static ResourceManager instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    // Function to get a texture resource
    std::shared_ptr<Texture> getTexture(const std::string& filename) {
        // Check if the texture is already loaded
        auto it = textures_.find(filename);
        if (it != textures_.end()) {
            // Texture is already loaded, return it
            return it->second;
        }

        // Texture not found, create a new one
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename);
        textures_[filename] = texture; // Store the texture in the map
        return texture;
    }

private:
    ResourceManager() = default; // Private constructor
    std::map<std::string, std::shared_ptr<Texture>> textures_; // Map to store textures
};

// Example usage
int main() {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Load textures
    auto texture1 = resourceManager.getTexture("grass.png");
    auto texture2 = resourceManager.getTexture("water.png");
    
    // Use textures
    texture1->use();
    texture2->use();

    // Load the same texture again to demonstrate the singleton behavior
    auto texture1Again = resourceManager.getTexture("grass.png");
    texture1Again->use(); // This should not load the texture again

    return 0;
}
