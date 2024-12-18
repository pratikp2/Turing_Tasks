#include <iostream>
#include <vector>
#include <unordered_map>

class Sprite {
public:
    Sprite(int id) : id(id) {
        std::cout << "Sprite " << id << " created.\n";
    }

    virtual ~Sprite() {
        std::cout << "Sprite " << id << " destroyed.\n";
    }

    void update() {
        // Update logic for the sprite
    }

    int getID() { return id; }

private:
    int id;
};

class SpritePool {
public:
    SpritePool(size_t capacity) {
        sprites.reserve(capacity);
        for (size_t i = 0; i < capacity; ++i) {
            sprites.push_back(std::make_unique<Sprite>(i));
        }
    }

    std::unique_ptr<Sprite> allocateSprite() {
        if (freeSprites.empty()) {
            // If no free sprites are available, create more (optional implementation)
            std::cerr << "Sprite pool exhausted!" << std::endl;
            return nullptr;
        }

        auto index = freeSprites.back();
        freeSprites.pop_back();
        return std::move(sprites[index]);
    }

    void freeSprite(std::unique_ptr<Sprite> sprite) {
        for (size_t i = 0; i < sprites.size(); ++i) {
            if (sprites[i]->getID() == sprite->getID()) {
                freeSprites.push_back(i);
                return;
            }
        }
        // If the sprite is not found in the pool, it may have been created outside the pool
        std::cerr << "Sprite not found in the pool!" << std::endl;
    }

private:
    std::vector<std::unique_ptr<Sprite>> sprites;
    std::vector<size_t> freeSprites;
};

int main() {
    const size_t NUM_SPRITES = 10;
    SpritePool spritePool(NUM_SPRITES);

    // Creating and using sprites from the pool
    for (int i = 0; i < NUM_SPRITES * 2; ++i) {
        auto sprite = spritePool.allocateSprite();
        if (sprite) {
            std::cout << "Using Sprite " << sprite->getID() << " in the simulation.\n";
            // Simulate using the sprite
        }
    }

    // Simulating sprites being removed from use and returned to the pool
    for (size_t i = 0; i < 3; ++i) {
        spritePool.freeSprite(std::make_unique<Sprite>(i));
    }

    return 0;
}
