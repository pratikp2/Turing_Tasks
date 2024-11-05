// Incorrect: Aligning to 4 bytes for a 8-byte type
alignas(4) double myDouble;

// Correct: Aligning to 8 bytes for a 8-byte type
alignas(8) double myDouble;
#pragma pack(push, 1)
struct MyStruct {
	char c;
	int i;
};
#pragma pack(pop)
int* aligned_ptr = static_cast<int*>(aligned_alloc(64, sizeof(int) * array_size));
