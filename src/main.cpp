#include "Archiver.hpp"
#include "RLEStrategy.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <compress|decompress> <input> <output>\n";
        return 1;
    }

    string mode = argv[1];
    filesystem::path input = argv[2];
    filesystem::path output = argv[3];

    Archiver archiver(make_unique<RLEStrategy>());

    if (mode == "compress") {
        if (!archiver.compress(input, output)) {
            cerr << "Compression failed\n";
            return 1;
        }
        archiver.print_report();
    } else if (mode == "decompress") {
        if (!archiver.decompress(input, output)) {
            cerr << "Decompression failed\n";
            return 1;
        }
    } else {
        cerr << "Invalid mode\n";
        return 1;
    }

    return 0;
}