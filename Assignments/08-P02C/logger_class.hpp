#pragma once
#include <ncurses.h>

#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

class Logger {
   public:
    // Set the log file path
    static void setFilePath(const std::string& filename) { filePath = filename; }

    static void clearLogFile() {
        if (!logging)
            return;
        std::lock_guard<std::mutex> lock(fileMutex);  // Thread-safe access
        std::ofstream file(filePath, std::ios::trunc);
        if (file.is_open()) {
            file << "Log file cleared." << std::endl;
        }
    }

    // Log a single key-value pair (string, string)
    static void log(const std::string& key, const std::string& value) {
        if (!logging)
            return;
        std::lock_guard<std::mutex> lock(fileMutex);  // Thread-safe access
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << key << ": " << value << std::endl;
        }
    }

    // Log multiple values under a single key (string, vector<string>)
    static void log(const std::string& key, const std::vector<std::string>& values) {
        if (!logging)
            return;
        std::lock_guard<std::mutex> lock(fileMutex);  // Thread-safe access
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << key << ": [";
            for (size_t i = 0; i < values.size(); ++i) {
                file << values[i];
                if (i != values.size() - 1)
                    file << ", ";
            }
            file << "]" << std::endl;
        }
    }

    static void log(const std::string& key, const std::vector<int>& values) {
        if (!logging)
            return;
        std::lock_guard<std::mutex> lock(fileMutex);  // Thread-safe access
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << key << ": [";
            for (size_t i = 0; i < values.size(); ++i) {
                file << values[i];
                if (i != values.size() - 1)
                    file << ", ";
            }
            file << "]" << std::endl;
        }
    }

    // Log all key-value pairs in a map (map<string, string>)
    static void log(const std::map<std::string, std::string>& keyValuePairs) {
        if (!logging)
            return;
        std::lock_guard<std::mutex> lock(fileMutex);  // Thread-safe access
        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            for (const auto& pair : keyValuePairs) {
                file << pair.first << ": " << pair.second << std::endl;
            }
        }
    }

    static void printLastLine(WINDOW* win) {
        if (!logging)
            return;
        std::ifstream file(filePath, std::ios::in | std::ios::ate);  // Open at end of file
        std::string lastLine;

        if (file.is_open()) {
            // Start reading from the end of the file
            file.seekg(-1, std::ios::end);

            // Check for a newline character or end of file
            bool isLastLineEmpty = (file.peek() == '\n');
            while (file.tellg() > 0) {
                char ch;
                file.seekg(-1, std::ios::cur);  // Move one character back
                ch = file.get();

                if (ch == '\n' && !isLastLineEmpty) {
                    break;
                }

                if (ch != '\n') {
                    lastLine.insert(lastLine.begin(), ch);  // Insert character at the beginning
                    file.seekg(-1, std::ios::cur);
                }
                isLastLineEmpty = false;
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filePath << std::endl;
        }
        int h, w;  // height and width of window
        getmaxyx(win, h, w);
        mvwprintw(win, 0, 0, "%-*s", w, " ");  // blank out entire top line
        mvwprintw(win, 0, 0, lastLine.c_str());
        return;
    }

   private:
    static std::string filePath;
    static std::mutex fileMutex;  // Mutex to ensure thread-safe file writing
    static bool logging;
};

// Define the static member variables
std::string Logger::filePath = "log.txt";
std::mutex Logger::fileMutex;
bool Logger::logging = true;