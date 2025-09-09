# Advanced File Archiver  
A sleek C++17 command-line tool that compresses and decompresses files using Run-Length Encoding (RLE). Perfect for squashing repetitive data into compact archives with a simple interface.

### Features  
Compress directories into a single .arc file using RLE.  
Decompress archives to restore original files.  
Detailed compression reports with size and ratio stats.  
Built with modern C++ and CMake for easy setup.  

### Prerequisites  
C++17 compatible compiler (e.g., g++)  
CMake 3.10+  
MinGW (Windows) or equivalent for other platforms  

### Installation  

**Clone the repo:-**  
git clone https://github.com/mannat-07/Advanced_File_Archiver.git  
cd Advanced_File_Archiver  

**Build the project:-**  
mkdir build && cd build  
cmake .. -G "MinGW Makefiles"  
mingw32-make  

### Project Structure  

src/: Source files (Archiver.cpp, RLEStrategy.cpp, main.cpp)  
include/: Headers (Archiver.hpp, CompressionStrategy.hpp, RLEStrategy.hpp)  
test/: Sample input files  
CMakeLists.txt: Build configuration  

### How to use  

**Compress a directory:-** ./archiver.exe compress <input_directory> <output_file>  
**Example:-** ./archiver.exe compress ../test ../archive.arc  

**Decompress an archive:-** ./archiver.exe decompress <input_file> <output_directory>  
**Example:-** ./archiver.exe decompress ../archive.arc ../restored_dir  


**Try It Out-->**  
The test directory includes sample files:  

first.txt: "AAAAA BBBBB"  
second.txt: "CCCCCCCC"  

Run:  
```./archiver.exe compress ../test ../archive.arc```  
```./archiver.exe decompress ../archive.arc ../restored_dir```  

Expected compression output:-  
Compressed file: first.txt (10 -> 4 bytes)  
Compressed file: second.txt (8 -> 4 bytes)  
Compression completed successfully  
Report:  
Method: RLE  
Original: 18 bytes  
Compressed: 8 bytes  
Ratio: 44.4444%  


Expected decompression output:-  
Opening archive: ../archive.arc  
Reading file name (size: 9)  
Processing file: first.txt  
Reading compressed data (size: 4)  
Decompressed file: ../restored_dir/first.txt (10 bytes)  
Reading file name (size: 10)  
Processing file: second.txt  
Reading compressed data (size: 4)  
Decompressed file: ../restored_dir/second.txt (8 bytes)  
Reached end of archive file  
Decompression completed successfully  