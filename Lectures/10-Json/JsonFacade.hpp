///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Tery Griffin
// Email:            terry.griffin@msutexas.edu
// Title:            JsonFacade
//
// Description:
//          This class is a facade pattern that simplifies the use of a very nicely written
//          hpp file from here: https://github.com/nlohmann/json 
//          
//          There is a lot of functionality that the header file includes, that we don't need.
//          This class lets a student treat a json array objects as an array. 
//
// Usage:
//
//      J = new JsonFacade("file_to_read");
//      size = J->getSize();                    // get array size
//
//      for (int i = 0; i < size; i++) {
//          obj = J->getNext();                 // read next object in json array
//          // do something with your json object
//      }
//
// Files:           
//      json.hpp
/////////////////////////////////////////////////////////////////////////////////
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

#include "json.hpp"

//using namespace std;

using json = nlohmann::json;

class JsonFacade {
private:
    json Data;
    int Size;
    int Index;
    std::string FileName;
    std::vector<std::string> Keys;
    std::vector<std::string> Values;
    

public:
    /**
     * JsonFacade: constructor that reads a file containing json and subsequently creates
     *             an array of dictionaries. 
     * 
     * Params:
     *     std::string filename : the filename containing the json to be read
     * 
     */
    JsonFacade(std::string filename) {
        FileName = filename;

        std::ifstream input(FileName);
        input >> Data;
        input.close();

        Size = Data.size();

        // c++ 17 issues so commented out
        // for (auto& [key, value] : Data.items()) {
        //     Keys.push_back(key);
        //     Values.push_back(value);
        // }
        
        // reverting to older implementation
        for (json::iterator it = Data.begin(); it != Data.end(); ++it) {
            Keys.push_back(it.key());
            Values.push_back(it.value());
        }
        Index = 0;
    }

    /**
     * getKeys: gets a std::vector of keys
     * 
     * returns:
     *      
     */
    std::vector<std::string> getKeys(){
        return Keys;
    }

    /**
     * getKey: gets a key at position i
     * 
     * 
     */
    std::string getKey(int i){
        return Keys[i];
    }
    
    /**
     * getValue: gets a value at array[key]
     * 
     * 
     */
    std::string getValue(std::string key){
        return Data[key];
    }


    /**
     * getNext: gets the "next" value in the array. Used to
     *          traverse the array with directly accessing it.
     * 
     * 
     */
    json getNext() {
        if (Index < Size) {
            return Data[Index++];
        }
        return NULL;
    }

    /**
     * getIth: gets the Ith json object from the array 
     * 
     * 
     */
    json getIth(int i) {
        if (i < Size) {
            return Data[i];
        }
        return NULL;
    }

    /**
     * pushBack: converts a std::string to json and pushes on end of array
     * 
     * Params:
     *     std::string obj  : a std::string json object which would be in the following format:
     * 
     *                "{\"key0\":"value0",\"key1\":1,\"keyn\":\"valuen"\}"
     * Returns:
     *     void
     *                
     */ 
    void pushBack(std::string obj){
        
        json j = json::parse(obj);
        Data.push_back(j);
        std::cout << Data.dump(4) << std::endl;
    }

    /** 
     * getSize: returns the size of the json object (count of objects)
     * 
     */
    int getSize() {
        return Size;
    }

    /**
     * saveFile: saves the json object to a file
     * 
     * Params:
     * 
     *     std::string filename : a filename to save object to. Defaults to 
     *                       name passed into constructor, meaning it will
     *                       overwrite the original file!
     *  Returns:
     *     NULL
     */
    void saveFile(std::string filename = ""){
        if(filename == ""){
            filename = FileName;
        }
        
        std::ofstream out(filename);
        out << std::setw(4) << Data << std::endl;
        out.close();
    }
};
