
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Define a PatientRecord struct to represent each patient record
struct PatientRecord {
    std::string name;
    std::string diagnosis;
};

// Function to perform data segmentation
std::unordered_map<std::string, std::vector<PatientRecord>> segmentData(const std::vector<PatientRecord>& records) {
   std::unordered_map<std::string, std::vector<PatientRecord>> segmentationResult;

   // Sort the records based on the 'diagnosis' field
   std::sort(records.begin(), records.end(), [](const PatientRecord& a, const PatientRecord& b) {
        return a.diagnosis < b.diagnosis;
    });

    // Iterate through the sorted records and segment the data
    for (const PatientRecord& record : records) {
        segmentationResult[record.diagnosis].push_back(record);
    }

    return segmentationResult;
}

int main() {
    // Toy dataset of patient records
    std::vector<PatientRecord> patientRecords = {
        {"Patient1", "Diabetes"},
        {"Patient2", "Diabetes"},
        {"Patient3", "Cancer"},
        {"Patient4", "Cancer"},
        {"Patient5", "Cancer"},
        {"Patient6", "Arthritis"},
        {"Patient7", "Arthritis"},
    };
 
    // Analyze and perform data segmentation
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, std::vector<PatientRecord>> segmentedData = segmentData(patientRecords);
    auto end = std::chrono::high_resolution_clock::now();
    
    // Display the segmentation result
    for (const auto& entry : segmentedData) {
        std::cout << "Diagnosis: " << entry.first << std::endl;
        for (const PatientRecord& record : entry.second) {
            std::cout << "   " << record.name << std::endl;
        }
        std::cout << std::endl;
    }

    // Calculate and display the execution time
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << time_span.count() << " seconds" << std::endl;

    return 0;
}  
  