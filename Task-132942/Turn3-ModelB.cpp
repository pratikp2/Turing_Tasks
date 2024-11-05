#include <cstddef>
#include <cstdlib>

template <std::size_t Alignment>
class AlignedAllocator {
public:
    using value_type = void;

    static void* allocate(std::size_t size) {
        return std::align(Alignment, size, nullptr, size);
    }

    static void deallocate(void* ptr, std::size_t size) {
        std::free(ptr);
    }
};
#include <array>
using AlignedIntArray = std::array<int, 1000, AlignedAllocator<16>>;
