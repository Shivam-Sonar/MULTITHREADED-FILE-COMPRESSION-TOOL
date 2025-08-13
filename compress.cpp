#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <zlib.h>

// Function to compress a block of data and measure the time taken
void compress_file_block(const std::string& input_filepath, long block_start, long block_size, int thread_id) {
    try {
        auto start_time = std::chrono::high_resolution_clock::now();

        // Open the input file
        std::ifstream input_file(input_filepath, std::ios::binary);
        if (!input_file) {
            throw std::runtime_error("Could not open input file.");
        }

        // Seek to the start of the block
        input_file.seekg(block_start);

        // Read the file block into a buffer
        std::vector<char> input_buffer(block_size);
        input_file.read(input_buffer.data(), block_size);
        input_file.close();

        // Prepare the output buffer for compressed data
        uLong compressed_size = compressBound(block_size);
        std::vector<Bytef> compressed_buffer(compressed_size);

        // Compress the data using zlib
        if (compress(compressed_buffer.data(), &compressed_size, (const Bytef*)input_buffer.data(), block_size) != Z_OK) {
            throw std::runtime_error("Compression failed.");
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_taken = end_time - start_time;

        std::cout << "Thread " << thread_id << ": Compressed " << block_size << " bytes to " << compressed_size << " bytes in " << time_taken.count() << " ms." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error in thread " << thread_id << ": " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <num_threads>" << std::endl;
        return 1;
    }

    std::string input_filepath = argv[1];
    int num_threads = std::stoi(argv[2]);

    if (num_threads <= 0) {
        std::cerr << "Number of threads must be a positive integer." << std::endl;
        return 1;
    }

    // Open the input file to get its size
    std::ifstream input_file(input_filepath, std::ios::binary | std::ios::ate);
    if (!input_file) {
        std::cerr << "Could not open input file to determine its size." << std::endl;
        return 1;
    }
    long file_size = input_file.tellg();
    input_file.close();

    if (file_size == 0) {
        std::cout << "Input file is empty. Nothing to compress." << std::endl;
        return 0;
    }

    // Calculate the size of each block
    long block_size = file_size / num_threads;
    long last_block_size = block_size + (file_size % num_threads);

    std::vector<std::thread> threads;

    std::cout << "Starting compression with " << num_threads << " threads." << std::endl;

    // Launch threads
    for (int i = 0; i < num_threads; ++i) {
        long current_block_start = i * block_size;
        long current_block_size = (i == num_threads - 1) ? last_block_size : block_size;
        threads.emplace_back(compress_file_block, input_filepath, current_block_start, current_block_size, i);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Compression finished." << std::endl;

    return 0;
}
