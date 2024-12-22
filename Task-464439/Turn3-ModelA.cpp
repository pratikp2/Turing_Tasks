void process(int *array, int size) { /* ... */ }
int main() {
    int arr[10];
    process(arr); // Size of arr is not accessible in process
}
