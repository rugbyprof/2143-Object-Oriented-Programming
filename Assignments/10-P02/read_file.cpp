#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

/**
 * Crappy function to clean leading and trailing spaces from 
 * a string. 
 */
string trim(string stuff){
    int start = 0;
    int end = stuff.size()-1;
    for(int i=0;i<stuff.size();i++,start++){
        if(stuff[i] != ' '){
            break;
        }
    }
    for(int i=stuff.size()-1;i>=0;i--,end--){
        if(stuff[i] != ' '){
            break;
        }
    }
    return stuff.substr(start,end-start-2); 
}

/**
 * Splits a string on a given delimiter and returns a vector
 * with each individual token.
 * 
 * Example:
 * 
 *      string test = "  one, two  , three, four,    five   ";
 *      test = splitString(test,',');
 *      
 *      would result in a vector with: ["one","two","three","four","five"]
 * 
 */
vector< string > splitString(string the_string, char delimiter) {
    vector< string > result;
    stringstream     s_stream(the_string);  //create string stream from the string
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, delimiter);  //get first string delimited by comma
        result.push_back(trim(substr));
    }
    return result;
}

int main() {
    ifstream fin;
    fin.open("small_input_example.txt");
    string line;
    vector<string> result;

    while(!fin.eof()){
        result.clear();
        getline(fin,line);
        result = splitString(line,',');
        if(result.size() > 1){
            
            for (int i = 0; i < result.size(); i++) {  //print all splitted strings
                cout << result.at(i) << endl;
            }
        }else{
            cout<<result[0]<<endl;
        }
        
    }


    return 0;
}