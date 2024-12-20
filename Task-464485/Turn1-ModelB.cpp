// Simple example of memory pool allocation (without error handling)
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    void* data;
    size_t size;
    struct block* next;
} block;

block* head = NULL;
size_t pool_size = 0;

void init_pool(size_t size) {
    head = (block*)malloc(size);
    pool_size = size;
}

void* allocate_from_pool(size_t size) {
    if (size == 0) return NULL;

    block* current = head;
    while (current) {
        if (current->size >= size) {
            block* new_block = (block*)((char*)current->data + size);
            new_block->size = current->size - size;
            new_block->next = current->next;
            current->size = size;
            current->next = new_block;
            return current->data;
        }
        current = current->next;
    }

    fprintf(stderr, "Memory pool exhausted\n");
    return NULL;
}

void free_to_pool(void* ptr) {
    if (ptr == NULL) return;

    block* current = head;
    while (current) {
        if (current->data == ptr) {
            if (current->next) {
                current->data = current->next->data;
                current->size = current->next->size;
                free(current->next);
            } else {
                free(current);
                if (head == current) head = NULL;
            }
            return;
        }
        current = current->next;
    }
}

int main() {
    init_pool(1024); // Preallocate 1KB memory pool

    void* ptr1 = allocate_from_pool(200);
    void* ptr2 = allocate_from_pool(300);

    // Use the allocated memory

    free_to_pool(ptr2);
    free_to_pool(ptr1);

    return 0;
}
// Simple example of a smart pointer
typedef struct {
    void* ptr;
} smart_ptr;

smart_ptr allocate(size_t size) {
    smart_ptr p;
    p.ptr = malloc(size);
    return p;
}

void deallocate(smart_ptr* p) {
    if (p->ptr) {
        free(p->ptr);
        p->ptr = NULL;
    }
}

int main() {
    smart_ptr ptr = allocate(100);

    // Use the allocated memory through ptr

    deallocate(&ptr); // Or you can let it go out of scope for automatic deallocation
    return 0;
}
