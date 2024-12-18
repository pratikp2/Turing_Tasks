#include <iostream>
#include <vector>
#include <memory>

class Particle {
public:
    Particle() : x(0), y(0), alive(false) {}

    void reset() {
        x = 0;
        y = 0;
        alive = true;
    }

    void update() {
        // Update particle's position (simple simulation)
        x += 1; // Move to the right
        y += 1; // Move downwards
        // Optionally mark the particle as dead based on some condition
        if (x > 100 || y > 100) alive = false; // Particle dies when it goes out of bounds
    }

    bool isAlive() const { return alive; }

private:
    float x, y;
    bool alive;
};

class ParticlePool {
public:
    ParticlePool(size_t size) {
        particles.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            particles.push_back(std::make_unique<Particle>());
        }
    }

    Particle* acquire() {
        for (auto& particle : particles) {
            if (!particle->isAlive()) {
                particle->reset();
                return particle.get();
            }
        }
        // Optionally, you can throw an exception or handle it gracefully
        return nullptr; // No available particles
    }

    void release(Particle* particle) {
        // Here you would handle any cleanup if necessary.
        // For this simple example, we don't need to do anything specific.
    }

    void update() {
        for (auto& particle : particles) {
            if (particle->isAlive()) {
                particle->update();
            }
        }
    }

private:
    std::vector<std::unique_ptr<Particle>> particles;
};

int main() {
    ParticlePool pool(10); // Create a pool with 10 particles

    for (int i = 0; i < 15; ++i) { // Simulate acquiring and updating particles
        Particle* p = pool.acquire();
        if (p) {
            std::cout << "Particle acquired and activated.\n";
            // Update particle for this frame
            pool.update();
            // Normally, you would release it once it's no longer needed.
            pool.release(p);
        } else {
            std::cout << "No available particles!\n";
        }
    }

    // Final update to see if any particles are still alive
    pool.update();

    return 0;
}
