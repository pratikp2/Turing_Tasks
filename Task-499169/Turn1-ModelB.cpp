#include <iostream>
#include <pthread.h>
#include <cstring>

using namespace std;

// Shared document data
char sharedDocument[1000] = {};
const int MAX_DOCUMENT_LENGTH = sizeof(sharedDocument) - 1;
pthread_mutex_t documentMutex = PTHREAD_MUTEX_INITIALIZER;

// Function to append text to the shared document
void appendText(const char* textToAppend) {
    int textLength = strlen(textToAppend);
    pthread_mutex_lock(&documentMutex);

    int currentDocumentLength = strlen(sharedDocument);
    if (currentDocumentLength + textLength <= MAX_DOCUMENT_LENGTH) {
        strcat(sharedDocument, textToAppend);
    } else {
        cout << "Document is full." << endl;
    }

    pthread_mutex_unlock(&documentMutex);
}

// Function to read the shared document
const char* readDocument() {
    pthread_mutex_lock(&documentMutex);
    const char* readData = sharedDocument;
    pthread_mutex_unlock(&documentMutex);
    return readData;
}

int main() {
    // Example usage with multiple threads
    pthread_t thread1, thread2;

    const char* textForThread1 = "Hello, ";
    const char* textForThread2 = "world!";

    pthread_create(&thread1, nullptr, [](void*) {
        appendText(textForThread1);
    }, nullptr);

    pthread_create(&thread2, nullptr, [](void*) {
        appendText(textForThread2);
    }, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    cout << "Shared Document: " << readDocument() << endl;

    return 0;
}
