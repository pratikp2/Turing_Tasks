#include <iostream>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

class Document {
private:
    char content[1024]; // Character array for document content
    std::mutex mtx; // Mutex for synchronizing access

public:
    Document() {
        strcpy(content, ""); // Initialize with an empty document
    }

    // Function to get the current content (for viewing)
    const char* getContent() {
        std::lock_guard<std::mutex> lock(mtx);
        return content;
    }

    // Function to modify the document content
    void editContent(const char* newContent) {
        std::lock_guard<std::mutex> lock(mtx);
        // Example of appending new content
        if (strlen(content) + strlen(newContent) < sizeof(content)) {
            strcat(content, newContent);
        } else {
            std::cerr << "Content exceeds maximum size!" << std::endl;
        }
    }
};

// Simulate a user editing the document
void userEdit(Document& doc, const char* editText, int userId) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * userId)); // Simulate latency
    std::cout << "User " << userId << " editing document..." << std::endl;
    doc.editContent(editText);
    std::cout << "Document after User " << userId << ": " << doc.getContent() << std::endl;
}

int main() {
    Document doc;

    // Simulate multiple users editing the document concurrently
    std::vector<std::thread> users;
    users.emplace_back(userEdit, std::ref(doc), "Hello, ", 1);
    users.emplace_back(userEdit, std::ref(doc), "World! ", 2);
    users.emplace_back(userEdit, std::ref(doc), "Goodbye! ", 3);

    for (auto& user : users) {
        user.join();
    }

    std::cout << "Final Document: " << doc.getContent() << std::endl;

    return 0;
}
