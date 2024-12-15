#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Custom allocator that uses pre-allocation

struct Arena {
    size_t size;
    char* memory;
    char* next_free;
};

struct Arena* create_arena(size_t size) {
    struct Arena* arena = malloc(sizeof(struct Arena));
    arena->size = size;
    arena->memory = malloc(size);
    arena->next_free = arena->memory;
    return arena;
}

void* allocate_from_arena(struct Arena* arena, size_t size) {
    if (size == 0) {
        return NULL;
    }

    assert(size <= arena->size - (arena->next_free - arena->memory));

    void* ptr = arena->next_free;
    arena->next_free += size;
    return ptr;
}

void free_arena(struct Arena* arena) {
    free(arena->memory);
    free(arena);
}

int main() {
    size_t arena_size = 1024 * 100; // 100KB arena
    struct Arena* arena = create_arena(arena_size);

    // Pre-allocating multiple buffers from the arena
    void* buffer1 = allocate_from_arena(arena, 64);
    void* buffer2 = allocate_from_arena(arena, 32);
    void* buffer3 = allocate_from_arena(arena, 256);

    // Using the pre-allocated buffers
    char* str1 = buffer1;
    char* str2 = buffer2;
    char* str3 = buffer3;

    strcpy(str1, "Hello, world!");
    strcpy(str2, "This is a test.");
    strcpy(str3, "Buffer is larger than the str.");

    printf("Buffer 1: %s\n", str1);
    printf("Buffer 2: %s\n", str2);
    printf("Buffer 3: %s\n", str3);

    free_arena(arena);
    return 0;
}
