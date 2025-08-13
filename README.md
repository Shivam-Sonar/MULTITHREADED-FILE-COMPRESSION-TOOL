# MULTITHREADED-FILE-COMPRESSION-TOOL
*COMPANY NAME*:- CODTECH IT SOLUTIONS
*NAME*:- Sonar Shivam Suryanath
*INTERN ID*:- CT04DH2913
*DOMAIN*:- C++ Programming
*DURATION* :- 4 WEEKS
*MENTOR* :- Neela Santhosh Kumar
# DESCRIPTION
This C++ program performs multithreaded file compression using the zlib library. It reads an input file, splits it into multiple blocks based on the number of threads specified by the user, and compresses each block concurrently using separate threads. This approach improves compression performance, especially for large files on multi-core processors.The program includes the following standard and third-party libraries:
iostream: For standard input and output operations.
fstream: For file handling (reading and writing files).
vector: To manage dynamic arrays for input and output buffers.
thread: To create and manage threads.
chrono: To measure the time taken by each compression task.
stdexcept: For exception handling using runtime_error.
zlib.h: External library used for data compression
This mode allows the program to move directly to the end of the file and use tellg() to get the total file size.
The file is then divided into blocks based on the number of threads:
Each thread is assigned an equal-sized block.
The last thread gets the remaining extra bytes (if the file size isn’t perfectly divisible).The program launches a loop to create and run threads. Each thread is passed:
The file path
Starting position of its block.Size of its block.
Its thread ID.Threads are created using std::thread and stored in a std::vector for later joining.This is the main compression routine executed by each thread. It performs the following steps:
File Reading:
Opens the file in binary mode.
Seeks to the block's start position using seekg.
Reads block_size bytes into a std::vector<char>.
Compression:
Calculates the maximum possible size of the compressed block using compressBound().
Allocates a buffer to store the compressed data.
Compresses the data using zlib’s compress() function.
Timing:
Uses std::chrono::high_resolution_clock to measure how long the compression took.
Output:
Prints the original block size, compressed size, and time taken by each thread.
Error Handling:
Any exception or failure during reading or compression is caught and printed to std::cerr.
Features and Strengths
Multithreading: Utilizes all CPU cores to reduce total compression time.
Block-based Processing: Makes handling large files efficient and scalable.
Error Handling: Catches and reports problems per thread.
Time Measurement: Useful for performance benchmarking.
Output Not Saved: Compressed data is not written to disk or merged into a final file.
No Decompression Support: This is compression-only with no reverse operation implemented.
No Format Handling: Doesn’t generate .gz or .zip file formats — raw compression only.
File Must Exist: No check or fallback if the file is missing or unreadable.


OUTPUT:-
![Image](https://github.com/user-attachments/assets/489adf51-33c7-408b-b836-af5e48a0e069)




