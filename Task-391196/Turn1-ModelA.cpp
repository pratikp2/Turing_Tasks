#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// Simulate network communication using a simple queue
std::queue<std::string> network;
std::mutex networkMutex;
std::condition_variable networkCondition;

void sendData(const std::string& data) {
    {
        std::unique_lock<std::mutex> lock(networkMutex);
        network.push(data);
    }
    networkCondition.notify_one();
}

std::string receiveData() {
    std::string data;
    {
        std::unique_lock<std::mutex> lock(networkMutex);
        while (network.empty()) {
            networkCondition.wait(lock);
        }
        data = network.front();
        network.pop();
    }
    return data;
}

void process1() {
    std::unordered_set<int> set1 = {1, 2, 3, 4, 5};
    std::cout << "Process 1 Set: ";
    for (auto& num : set1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Send set1 to process2
    std::stringstream ss;
    for (auto& num : set1) {
        ss << num << " ";
    }
    sendData(ss.str());

    // Receive set2 from process2
    std::string set2Str = receiveData();
    std::unordered_set<int> set2;
    std::istringstream iss(set2Str);
    int num;
    while (iss >> num) {
        set2.insert(num);
    }

    std::cout << "Process 1 Received Set 2: ";
    for (auto& num : set2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Perform set operations
    std::unordered_set<int> unionSet;
    std::unordered_set<int> intersectionSet;

    std::copy(set1.begin(), set1.end(), std::inserter(unionSet, unionSet.end()));
    std::copy(set2.begin(), set2.end(), std::inserter(unionSet, unionSet.end()));

    std::copy(set1.begin(), set1.end(), std::inserter(intersectionSet, intersectionSet.end()));
    intersectionSet.erase(std::set_difference(intersectionSet.begin(), intersectionSet.end(), set2.begin(), set2.end()), intersectionSet.end());

    std::cout << "Process 1 Union: ";
    for (auto& num : unionSet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Process 1 Intersection: ";
    for (auto& num : intersectionSet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void process2() {
    std::unordered_set<int> set2 = {4, 5, 6, 7, 8};
    std::cout << "Process 2 Set: ";
    for (auto& num : set2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Receive set1 from process1
    std::string set1Str = receiveData();
    std::unordered_set<int> set1;
    std::istringstream iss(set1Str);
    int num;
    while (iss >> num) {
        set1.insert(num);
    }

    std::cout << "Process 2 Received Set 1: ";
    for (auto& num : set1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Perform set operations
    std::unordered_set<int> unionSet;
    std::unordered_set<int> intersectionSet;

    std::copy(set1.begin(), set1.end(), std::inserter(unionSet, unionSet.end()));
    std::copy(set2.begin(), set2.end(), std::inserter(unionSet, unionSet.end()));

    std::copy(set1.begin(), set1.end(), std::inserter(intersectionSet, intersectionSet.end()));
    intersectionSet.erase(std::set_difference(intersectionSet.begin(), intersectionSet.end(), set2.begin(), set2.end()), intersectionSet.end());

    std::cout << "Process 2 Union: ";
    for (auto& num : unionSet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Process 2 Intersection: ";
    for (auto& num : intersectionSet) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Send set2 to process1
    std::stringstream ss;
    for (auto& num : set2) {
        ss << num << " ";
    }
    sendData(ss.str());
}

int main() {
    std::thread thread1(process1);
    std::thread thread2(process2);

    thread1.join();
    thread2.join();

    return 0;
}
