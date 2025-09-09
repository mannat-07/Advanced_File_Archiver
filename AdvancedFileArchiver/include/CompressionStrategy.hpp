#pragma once
#include <vector>
#include <string>

using namespace std;

class CompressionStrategy {
public:
    virtual ~CompressionStrategy() = default;
    virtual vector<char> compress(const vector<char>& data) = 0;
    virtual vector<char> decompress(const vector<char>& data) = 0;
    virtual string get_name() const = 0;
};