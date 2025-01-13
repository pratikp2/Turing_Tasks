#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <fstream>


// --------------------------------------------------
//     Mock Network Library
// --------------------------------------------------
class NetworkLib {
public:
    virtual bool receiveChunk(uint8_t* buffer, size_t bufferSize) = 0;
    virtual size_t getTotalFirmwareSize() const = 0;
    virtual ~NetworkLib() = default;
};

class MockNetworkLib : public NetworkLib {
private:
    std::ifstream firmwareFile;
    size_t firmwareSize = 0;

public:
    MockNetworkLib(const std::string& firmwareFilePath) {
        firmwareFile.open(firmwareFilePath, std::ios::binary);
        if (!firmwareFile.is_open()) {
            throw std::runtime_error("Failed to open mock firmware file.");
        }
        firmwareSize = static_cast<size_t>(firmwareFile.tellg());
        firmwareFile.seekg(0, std::ios::beg);
    }

    ~MockNetworkLib() override {
        firmwareFile.close();
    }

    bool receiveChunk(uint8_t* buffer, size_t bufferSize) override {
        if (firmwareFile.eof()) {
            return false;
        }
        firmwareFile.read(reinterpret_cast<char*>(buffer), bufferSize);
        return true;
    }

    size_t getTotalFirmwareSize() const override {
        return firmwareSize;
    }
};
// --------------------------------------------------
//  Mock Flash Memory Library
// --------------------------------------------------
class FlashLib {
public:
    virtual void eraseAll() = 0;
    virtual void program(size_t address, const uint8_t* data, size_t size) = 0;
    virtual ~FlashLib() = default;
};

class MockFlashLib : public FlashLib {
private:
    std::vector<uint8_t> flashMemory;

public:
    MockFlashLib() = default;

    void eraseAll() override {
        flashMemory.clear();
    }

    void program(size_t address, const uint8_t* data, size_t size) override {
        if (address + size > flashMemory.size()) {
            throw std::runtime_error("Flash memory address out of bounds.");
        }
        flashMemory.replace(flashMemory.begin() + address, flashMemory.begin() + address + size, data, data + size);
    }
};

// --------------------------------------------------
//       Firmware Update Implementation
// --------------------------------------------------
void performFirmwareUpdate(NetworkLib& networkLib, FlashLib& flashLib) {
    const size_t bufferSize = 256; // Example buffer size
    uint8_t buffer[bufferSize];

    size_t totalSize = networkLib.getTotalFirmwareSize();
    size_t bytesWritten = 0;

    flashLib.eraseAll();

    std::cout << "Firmware update starting: Total size=" << totalSize << std::endl;

    while (bytesWritten < totalSize) {
        if (!networkLib.receiveChunk(buffer, bufferSize)) {
            throw std::runtime_error("Failed to receive firmware data from network.");
        }

        const size_t downloadedBytes = std::min(sizeof(buffer), totalSize - bytesWritten);
        flashLib.program(bytesWritten, buffer, downloadedBytes);

        bytesWritten += downloadedBytes;
        std::cout << "Bytes written: " << bytesWritten << "/" << totalSize << std::endl;
    }

    std::cout << "Firmware update completed successfully." << std::endl;
}
int main() {
    try {
        // Replace 'firmware.bin' with the path to your actual firmware binary file.
        MockNetworkLib networkLib("firmware.bin");
        MockFlashLib flashLib;

        performFirmwareUpdate(networkLib, flashLib);

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
