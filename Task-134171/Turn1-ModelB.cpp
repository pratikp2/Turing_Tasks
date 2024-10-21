#include <iostream>
#include <thread>
#include <vector>
#include <immintrin.h>  // For SIMD instructions

const int NUM_THREADS = 4;
const int NUM_ITERATIONS = 10000000;
const int VECTOR_SIZE = 4; // Number of elements per SIMD vector

class Particle {
public:
    float x, y, z;

    void update() {
        // Simple particle update function
        x += 0.1f;
        y += 0.1f;
        z += 0.1f;
    }
};

void updateParticlesSerial(std::vector<Particle>& particles) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (size_t j = 0; j < particles.size(); j++) {
            particles[j].update();
        }
    }
}

void updateParticlesParallel(std::vector<Particle>& particles) {
    int numParticlesPerThread = particles.size() / NUM_THREADS;

    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        int startIndex = i * numParticlesPerThread;
        int endIndex = std::min((i + 1) * numParticlesPerThread, particles.size());
        threads.emplace_back(std::thread(updateParticlesThread, std::ref(particles), startIndex, endIndex));
    }

    for (std::thread& thread : threads) {
        thread.join();
    }
}

void updateParticlesThread(std::vector<Particle>& particles, int startIndex, int endIndex) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = startIndex; j < endIndex; j++) {
            particles[j].update();
        }
    }
}

void updateParticlesSIMD(std::vector<Particle>& particles) {
    int numParticlesPerVector = particles.size() / VECTOR_SIZE;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        for (int j = 0; j < numParticlesPerVector; j++) {
            __m128 xVec = _mm_loadu_ps(&particles[j * VECTOR_SIZE].x);
            __m128 yVec = _mm_loadu_ps(&particles[j * VECTOR_SIZE].y);
            __m128 zVec = _mm_loadu_ps(&particles[j * VECTOR_SIZE].z);

            __m128 updateVal = _mm_set1_ps(0.1f);

            xVec = _mm_add_ps(xVec, updateVal);
            yVec = _mm_add_ps(yVec, updateVal);
            zVec = _mm_add_ps(zVec, updateVal);

            _mm_storeu_ps(&particles[j * VECTOR_SIZE].x, xVec);
            _mm_storeu_ps(&particles[j * VECTOR_SIZE].y, yVec);
            _mm_storeu_ps(&particles[j * VECTOR_SIZE].z, zVec);
        }
    }
}

int main() {
    std::vector<Particle> particles(100000);

    // Initialize particles
    for (size_t i = 0; i < particles.size(); i++) {
        particles[i].x = 0.0f;
        particles[i].y = 0.0f;
        particles[i].z = 0.0f;
    }

    // Serial execution
    auto serialStart = std::chrono::high_resolution_clock::now();
    updateParticlesSerial(particles);
    auto serialEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Serial execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(serialEnd - serialStart).count() << " ms" << std::endl;

    // Parallel execution
    auto parallelStart = std::chrono::high_resolution_clock::now();
    updateParticlesParallel(particles);
    auto parallelEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(parallelEnd - parallelStart).count() << " ms" << std::endl;

    // SIMD execution
    auto simdStart = std::chrono::high_resolution_clock::now();
    updateParticlesSIMD(particles);
    auto simdEnd = std::chrono::high_resolution_clock::now();
    std::cout << "SIMD execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(simdEnd - simdStart).count() << " ms" << std::endl;

    return 0;
}