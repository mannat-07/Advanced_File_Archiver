#include "Archiver.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Archiver::Archiver(unique_ptr<CompressionStrategy> strategy)
    : strategy(move(strategy)), original_size(0), compressed_size(0) {}

bool Archiver::compress(const filesystem::path& input_dir, const filesystem::path& output_file) {
    if (!filesystem::is_directory(input_dir)) {
        cerr << "Error: Not a directory: " << input_dir << "\n";
        return false;
    }

    ofstream out_file(output_file, ios::binary);
    if (!out_file) {
        cerr << "Error: Cannot open output file: " << output_file << "\n";
        return false;
    }

    original_size = 0;
    compressed_size = 0;

    for (const auto& entry : filesystem::directory_iterator(input_dir)) {
        if (filesystem::is_regular_file(entry)) {
            ifstream in_file(entry.path(), ios::binary);
            if (!in_file) {
                cerr << "Warning: Cannot open file " << entry.path() << "\n";
                continue;
            }

            vector<char> data((istreambuf_iterator<char>(in_file)), {});
            original_size += data.size();

            vector<char> compressed_data = strategy->compress(data);
            compressed_size += compressed_data.size();

            string file_name = entry.path().filename().string();
            uint32_t name_size = file_name.size();
            out_file.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));
            out_file.write(file_name.data(), name_size);

            uint32_t data_size = compressed_data.size();
            out_file.write(reinterpret_cast<const char*>(&data_size), sizeof(data_size));
            out_file.write(compressed_data.data(), data_size);

            cout << "Compressed file: " << file_name << " (" << data.size() << " -> " << compressed_data.size() << " bytes)\n";
        }
    }

    cout << "Compression completed successfully\n";
    return true;
}

bool Archiver::decompress(const filesystem::path& input_file, const filesystem::path& output_dir) {
    if (!filesystem::exists(input_file)) {
        cerr << "Error: Input file does not exist: " << input_file << "\n";
        return false;
    }

    ifstream in_file(input_file, ios::binary);
    if (!in_file) {
        cerr << "Error: Cannot open input file: " << input_file << "\n";
        return false;
    }

    cout << "Opening archive: " << input_file << "\n";
    filesystem::create_directories(output_dir);

    bool processed_any = false;
    while (in_file) {
        uint32_t name_size;
        in_file.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));
        if (!in_file) {
            if (in_file.eof() && !processed_any) {
                cout << "Archive is empty or invalid\n";
                break;
            } else if (in_file.eof()) {
                cout << "Reached end of archive file\n";
                break;
            }
            cerr << "Error: Failed to read name size\n";
            return false;
        }

        cout << "Reading file name (size: " << name_size << ")\n";
        string file_name(name_size, '\0');
        in_file.read(file_name.data(), name_size);
        if (!in_file) {
            cerr << "Error: Failed to read file name\n";
            return false;
        }

        cout << "Processing file: " << file_name << "\n";
        uint32_t data_size;
        in_file.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));
        if (!in_file) {
            cerr << "Error: Failed to read data size\n";
            return false;
        }

        cout << "Reading compressed data (size: " << data_size << ")\n";
        vector<char> compressed_data(data_size);
        in_file.read(compressed_data.data(), data_size);
        if (!in_file) {
            cerr << "Error: Failed to read compressed data\n";
            return false;
        }

        vector<char> decompressed_data = strategy->decompress(compressed_data);
        filesystem::path out_path = output_dir / file_name;

        ofstream out_file(out_path, ios::binary);
        if (!out_file) {
            cerr << "Error: Cannot open output file: " << out_path << "\n";
            return false;
        }
        out_file.write(decompressed_data.data(), decompressed_data.size());
        cout << "Decompressed file: " << out_path << " (" << decompressed_data.size() << " bytes)\n";

        processed_any = true;
    }

    if (processed_any) {
        cout << "Decompression completed successfully\n";
    }
    return true;
}

void Archiver::print_report() const {
    cout << "Report:\n";
    cout << "Method: " << strategy->get_name() << "\n";
    cout << "Original: " << original_size << " bytes\n";
    cout << "Compressed: " << compressed_size << " bytes\n";
    if (original_size > 0) {
        cout << "Ratio: " << (double)compressed_size / original_size * 100 << "%\n";
    }
}