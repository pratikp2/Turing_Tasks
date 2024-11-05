// Incorrect alignment: Using alignas(4) for 32-bit float on x86-64
   alignas(4) float* unaligned_floats = new float[array_size];
// Example of an incorrectly aligned struct
   struct MyStruct {
       int a; // 4-byte alignment
       double b; // 8-byte alignment
       char c; // 1-byte alignment
   }; // The struct will be aligned to 8 bytes due to 'double b'
int64_t* ptr = new int64_t[array_size];
   // The pointer 'ptr' is aligned to 8 bytes (assuming 64-bit architecture), but the array elements must be aligned to 8 bytes.
int* aligned_ptr;
   std::align(alignof(int), sizeof(int), &aligned_ptr, array_size * sizeof(int));
