
// file_change_detection.cpp
// A teaching demo showing three methods of file change detection in C++
// How To Compile:
//      g++ file_change_detection.cpp -o detect -lssl -lcrypto

#include <sys/stat.h>
#include <unistd.h>

#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

// Method 1: Timestamp-based detection
bool fileChangedTime(const std::string& filepath, time_t& last_modified) {
    struct stat file_stat;
    if (stat(filepath.c_str(), &file_stat) == 0) {
        if (file_stat.st_mtime != last_modified) {
            last_modified = file_stat.st_mtime;
            return true;
        }
    }
    return false;
}

// Method 2: Hash of file content using std::hash (not secure, just a demo)
bool fileChangedHash(const std::string& filepath, size_t& last_hash) {
    std::ifstream file(filepath);
    if (!file)
        return false;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::hash<std::string> hasher;
    size_t current_hash = hasher(content);

    if (current_hash != last_hash) {
        last_hash = current_hash;
        return true;
    }
    return false;
}

// Method 3: Cryptographic SHA1 using OpenSSL
#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

std::string sha1sum(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
        return "";

    SHA_CTX ctx;
    SHA1_Init(&ctx);

    char buffer[8192];
    while (file.read(buffer, sizeof(buffer))) {
        SHA1_Update(&ctx, buffer, file.gcount());
    }
    SHA1_Update(&ctx, buffer, file.gcount());

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &ctx);

    std::ostringstream oss;
    for (unsigned char c : hash) oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;

    return oss.str();
}

bool fileChangedSHA1(const std::string& filepath, std::string& last_sha1) {
    std::string current_sha1 = sha1sum(filepath);
    if (current_sha1.empty())
        return false;
    if (current_sha1 != last_sha1) {
        last_sha1 = current_sha1;
        return true;
    }
    return false;
}

int main() {
    std::string filepath = "example.txt";

    // Method 1
    time_t last_time = 0;
    if (fileChangedTime(filepath, last_time)) {
        std::cout << "[Time] File changed.\n";
    }

    // Method 2
    size_t last_hash = 0;
    if (fileChangedHash(filepath, last_hash)) {
        std::cout << "[Hash] File changed.\n";
    }

    // Method 3
    std::string last_sha1;
    if (fileChangedSHA1(filepath, last_sha1)) {
        std::cout << "[SHA1] File changed.\n";
    }

    return 0;
}

// Compile with: g++ file_change_detection.cpp -o detect -lssl -lcrypto
