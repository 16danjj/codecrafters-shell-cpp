#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>

using namespace std;

namespace shell::find_executable {

    bool file_find(const string& command){
        // executable with arguments related logic
        stringstream s1(command);
        string token;

        vector<string> temp_storage;
        bool file_found = false;

        while (getline(s1,token,' ')) {
            temp_storage.push_back(token);
        }

        // Check if executable exists 
        string path = getenv("PATH");
        stringstream s2(path);
        string unique_path;

        while (getline(s2,unique_path, ':')) {

            string full_path = unique_path + "/" + temp_storage[0];

            if (access(full_path.c_str(), X_OK) == 0) {
                system(command.c_str());
                file_found = true;
                break;
            }
            
        }

        return file_found;
    }
}