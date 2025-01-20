#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <filesystem>

// Forward declarations for Texture and Audio classes
class Texture {
public:
    explicit Texture(const std::string& filePath) {
        // Simulate loading the texture from a file
        if (!std::filesystem::exists(filePath)) {
            throw std::runtime_error("Texture file not found: " + filePath);
        }
        std::cout << "Loading texture from: " << filePath << std::endl;
    }
};

class Audio {
public:
    explicit Audio(const std::string& filePath) {
        // Simulate loading the audio file from a path
        if (!std::filesystem::exists(filePath)) {
            throw std::runtime_error("Audio file not found: " + filePath);
        }
        std::cout << "Loading audio from: " << filePath << std::endl;
    }
};

// ResourceLoader class for managing loaded textures and audio files
class ResourceLoader {
public:
    inline std::shared_ptr<Texture> LoadTexture(const std::string& filePath);
    inline std::shared_ptr<Audio> LoadAudio(const std::string& filePath);

private:
    // Caches for loaded resources
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureCache;
    std::unordered_map<std::string, std::shared_ptr<Audio>> audioCache;

    // Actual loading implementations
    std::shared_ptr<Texture> LoadTextureFromFile(const std::string& filePath);
    std::shared_ptr<Audio> LoadAudioFromFile(const std::string& filePath);
};

#endif // RESOURCE_LOADER_H

// Inline function to load or retrieve a cached texture
inline std::shared_ptr<Texture> ResourceLoader::LoadTexture(const std::string& filePath) {
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second; // Return cached texture
    }

    // Load new texture and cache it
    auto texture = LoadTextureFromFile(filePath);
    if (texture) {
        textureCache[filePath] = texture;
    }
    return texture;
}

// Inline function to load or retrieve a cached audio
inline std::shared_ptr<Audio> ResourceLoader::LoadAudio(const std::string& filePath) {
    auto it = audioCache.find(filePath);
    if (it != audioCache.end()) {
        return it->second; // Return cached audio
    }

    // Load new audio and cache it
    auto audio = LoadAudioFromFile(filePath);
    if (audio) {
        audioCache[filePath] = audio;
    }
    return audio;
}

// Load texture implementation with error handling
std::shared_ptr<Texture> ResourceLoader::LoadTextureFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Texture>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading texture from " << filePath << ": " << e.what() << std::endl;
        return nullptr; // Handle failed texture loading gracefully
    }
}

// Load audio implementation with error handling
std::shared_ptr<Audio> ResourceLoader::LoadAudioFromFile(const std::string& filePath) {
    try {
        return std::make_shared<Audio>(filePath);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error loading audio from " << filePath << ": " << e.what() << std::endl;
        return nullptr; // Handle failed audio loading gracefully
    }
}

int main() {
    ResourceLoader resourceLoader;

    // Load textures
    auto texture1 = resourceLoader.LoadTexture("assets/textures/texture1.png");
    auto texture2 = resourceLoader.LoadTexture("assets/textures/texture2.png");

    // Load the same texture again to demonstrate caching
    auto texture3 = resourceLoader.LoadTexture("assets/textures/texture1.png");
    
    if (texture1 == texture3) {
        std::cout << "Successfully reused cached texture1." << std::endl;
    }

    // Load audio files
    auto audio1 = resourceLoader.LoadAudio("assets/audio/sound1.wav");
    auto audio2 = resourceLoader.LoadAudio("assets/audio/sound2.wav");

    // Attempt to load a missing audio file
    auto audioMissing = resourceLoader.LoadAudio("assets/audio/missing_sound.wav");

    // Cleanup (if needed) would be handled by shared_ptr going out of scope

    return 0;
}
