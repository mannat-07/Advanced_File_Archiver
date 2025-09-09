#pragma once
#include "CompressionStrategy.hpp"

using namespace std;

class RLEStrategy : public CompressionStrategy {
public:
    vector<char> compress(const vector<char>& data) override;
    vector<char> decompress(const vector<char>& data) override;
    string get_name() const override { return "RLE"; }
};