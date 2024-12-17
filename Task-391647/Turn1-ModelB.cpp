#include <iostream>
#include <unordered_map>
#include <string>

class Texture {
public:
    Texture(const std::string& id) : m_id(id) {}
    virtual ~Texture() = default;
    const std::string& getId() const { return m_id; }

private:
    std::string m_id;
};

class ResourceManager {
private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    static ResourceManager* m_instance;
    std::unordered_map<std::string, Texture*> m_textures;

public:
    static ResourceManager& getInstance() {
        if (!m_instance) {
            m_instance = new ResourceManager();
        }
        return *m_instance;
    }

    void loadTexture(const std::string& id) {
        if (m_textures.find(id) == m_textures.end()) {
            m_textures[id] = new Texture(id);  
            std::cout << "Texture '" << id << "' loaded." << std::endl;
        } else {
            std::cout << "Texture '" << id << "' already loaded." << std::endl;
        }
    }

    Texture* getTexture(const std::string& id) const {
        auto it = m_textures.find(id);
        if (it != m_textures.end()) {
            return it->second;
        } else {
            std::cout << "Texture '" << id << "' not found." << std::endl;
            return nullptr;
        }
    }

    void unloadTexture(const std::string& id) {
        auto it = m_textures.find(id);
        if (it != m_textures.end()) {
            delete it->second;
            m_textures.erase(it);
            std::cout << "Texture '" << id << "' unloaded." << std::endl;
        } else {
            std::cout << "Texture '" << id << "' not found." << std::endl;
        }
    }

    void unloadAllTextures() {
        for (auto& texture : m_textures) {
            delete texture.second;
        }
        m_textures.clear();
        std::cout << "All textures unloaded." << std::endl;
    }
};

int main() {
    ResourceManager& rm = ResourceManager::getInstance();

    rm.loadTexture("grass.png");
    rm.loadTexture("tree.png");
    rm.loadTexture("grass.png");  

    Texture* grassTexture = rm.getTexture("grass.png");
    if (grassTexture) {
        std::cout << "Using texture 'grass.png' with ID: " << grassTexture->getId() << std::endl;
    }

    rm.unloadTexture("tree.png");

    rm.unloadAllTextures();

    return 0;
}
