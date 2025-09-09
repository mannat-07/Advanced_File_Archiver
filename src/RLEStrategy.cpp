#include "RLEStrategy.hpp"
#include <cstdint> // Added for uint8_t

using namespace std;

vector<char> RLEStrategy::compress(const vector<char>& data) {
    vector<char> result;
    for (size_t i = 0; i < data.size(); ) {
        char value = data[i];
        uint8_t count = 1;
        while (i + 1 < data.size() && data[i + 1] == value && count < 255) {
            ++i;
            ++count;
        }
        result.push_back(value);
        result.push_back(static_cast<char>(count));
        ++i;
    }
    return result;
}

vector<char> RLEStrategy::decompress(const vector<char>& data) {
    vector<char> result;
    for (size_t i = 0; i < data.size(); i += 2) {
        char value = data[i];
        uint8_t count = static_cast<uint8_t>(data[i + 1]);
        for (uint8_t j = 0; j < count; ++j) {
            result.push_back(value);
        }
    }
    return result;
}