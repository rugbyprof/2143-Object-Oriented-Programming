#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

bool fileChanged(const std::string& filepath, time_t& last_modified) {
    struct stat file_stat;

    // Retrieve file attributes
    if (stat(filepath.c_str(), &file_stat) == 0) {
        // Compare the last modification time with the stored value
        if (file_stat.st_mtime != last_modified) {
            last_modified = file_stat.st_mtime; // Update the stored modification time
            return true; // File has been modified
        }
    } else {
        std::cerr << "Error retrieving file information.\n";
    }
    return false; // No change
}

int main() {
    std::string filepath = "example.txt";
    time_t last_modified = 0;

    // Initial check
    if (fileChanged(filepath, last_modified)) {
        std::cout << "File has changed!\n";
    }

    // Simulate a periodic check
    sleep(10); // Wait for 10 seconds
    if (fileChanged(filepath, last_modified)) {
        std::cout << "File has changed again!\n";
    }

    return 0;
}