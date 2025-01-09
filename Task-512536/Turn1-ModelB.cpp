#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

// Base class for resources
class Resource {
public:
    Resource(const std::string& name) : name(name) {}
    virtual ~Resource() = default;

    virtual void use() const { std::cout << "Using resource: " << name << std::endl; }

    const std::string& getName() const { return name; }

private:
    const std::string name;
};

// Example of a Texture resource
class Texture : public Resource {
public:
    Texture(const std::string& name) : Resource(name) {}
};

// Resource manager
class ResourceManager {
public:
    template <typename T, typename... Args>
    std::shared_ptr<T> getResource(const std::string& name, Args&&... args) {
        if (auto existingResource = resources.find(name); existingResource != resources.end()) {
            return std::static_pointer_cast<T>(existingResource->second);
        }

        auto newResource = std::make_shared<T>(name, std::forward<Args>(args)...);
        resources[name] = newResource;
        return newResource;
    }

    void removeResource(const std::string& name) {
        resources.erase(name);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> resources;
};

int main() {
    ResourceManager resourceManager;

    // Load some textures
    auto texture1 = resourceManager.getResource<Texture>("texture1.png");
    auto texture2 = resourceManager.getResource<Texture>("texture2.png");

    // Use the textures
    texture1->use();
    texture2->use();

    return 0;
}
