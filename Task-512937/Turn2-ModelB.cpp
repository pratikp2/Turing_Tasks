template <int N>
void unrolledLoop() {
    // ...
}

int main() {
    unrolledLoop<10>(); // Compiler can unroll this loop 10 times
    // ...
}
