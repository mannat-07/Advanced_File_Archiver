#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include "CompressionStrategy.hpp"

using namespace std;

class Archiver {
private:
    unique_ptr<CompressionStrategy> strategy;
    size_t original_size;
    size_t compressed_size;

public:
    Archiver(unique_ptr<CompressionStrategy> strategy);
    bool compress(const filesystem::path& input_dir, const filesystem::path& output_file);
    bool decompress(const filesystem::path& input_file, const filesystem::path& output_dir);
    void print_report() const;
};