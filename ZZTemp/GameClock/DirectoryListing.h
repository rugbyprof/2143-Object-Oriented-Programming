#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "dirent.h"

using namespace std;

/**
 * Class: DirectoryListing
 *     Creates a vector of filenames based on a given string path.
 * 
 */
class DirectoryListing {
protected:
    DIR* Dir;                   // Directory reference variable
    struct dirent* ent;         // Struct that holds filename information
    string DirName;             // The directory name we want to list
    vector<string> FileNames;   // Filenames if the directory exists

public:
    /**
     * Constructor 
     * @Param:
     *    dir_name {string} : a directory path to read
     */
    DirectoryListing(string dir_name = "")
    {
        DirName = _fixDirName(dir_name);
    }

    /**
     * scanDir - scans the directory 
     * @Param:
     *    dir_name {string} : path to directory (e.g. "./images" or "C://folder/to/stuff")
     * @Return:
     *    vector<string> : containing the file names.
     */
    vector<string> scanDir(string dir_name="")
    {
        // If there is a directory name, fix it and get the files
        if(dir_name.size() > 0){
            DirName = _fixDirName(dir_name);

        // If there is an existing directory name, get its files
        // otherwise return an empty vector.
        }else if(DirName.size() == 0){

            return vector<string>();
        }

        string fname;   // temp variable for readability

        // If we manage to open the directory
        if ((Dir = opendir(DirName.c_str())) != NULL) {

            // Loop through the dirctory reference and load up a vector
            while ((ent = readdir(Dir)) != NULL) {
                fname = ent->d_name;

                // Linux directories have a "." and a ".." that we 
                // want to ignore.
                if (fname != "." && fname != "..") {

                    FileNames.push_back(fname); // add filename to vector
                }
            }
            closedir(Dir);
        } else {
            /* could not open directory so error*/
            std::cout << "Error: Could not open directory. Error number: " << EXIT_FAILURE << std::endl;
        }

        //Sort the filenames for no particular reason
        sort(FileNames.begin(), FileNames.end());
        return FileNames;
    }

    /**
     * stdPrintDir - prints vector contents to standard out for debugging
     * @Param:
     *    None
     * @Return:
     *    None
     */
    void stdPrintDir()
    {
        for (int i = 0; i < FileNames.size(); i++) {
            std::cout << FileNames[i] << std::endl;
        }
    }

private:
    /**
     * _fixDirName : checks for a trailing slash, and strips it off.
     *               Why? We always append a slash when concatenating filenames.
     *               Example: ./images/ would become ./images//filename.png so we strip it off.
     * @Param:
     *    name {string} directory name
     * @Return:
     *    string : fixed name
     */
    string _fixDirName(string name)
    {
        if (name[name.size() - 1] == '/') {
            name.pop_back();
        }
        return name;
    }
};