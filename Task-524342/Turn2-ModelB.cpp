int main() {
    try {
        {
            DynamicArray arr1(0); // Size is zero
        }
        
        {
            DynamicArray arr2(1000000000); // This will likely fail due to memory exhaustion
        }

        DynamicArray arr3(5);
        for (size_t i = 0; i < arr3.size(); ++i) {
            arr3[i] = i + 1;
        }

        // Function that throws an exception
        funcThatThrowsException();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
