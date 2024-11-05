// RedundantDataStructure.h
#include <vector>
#include <string>

#include "error_correcting_code.h"

class RedundantDataStructure {
public:
    RedundantDataStructure(size_t size, size_t redundancy_factor) :
        size_(size), redundancy_factor_(redundancy_factor),
        data_(size_ * (1 + redundancy_factor_)),
        code_(size_, redundancy_factor_) {}

    void setData(const std::string& data) {
        code_.encode(data, data_.data());
    }

    std::string getData() {
        std::string decoded_data(size_, '\0');
        code_.decode(data_.data(), decoded_data.data());
        return decoded_data;
    }

private:
    size_t size_;
    size_t redundancy_factor_;
    std::vector<char> data_;
    ErrorCorrectingCode code_;
};
