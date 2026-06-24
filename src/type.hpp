#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>

using namespace std;

namespace shell::type {
        int execute(const string& input){

            bool file_found = false;

            if (input == "echo" || input == "exit" || input == "type" || input == "pwd") {
                cout << input << " is a shell builtin" << endl;
            } 
            
            else {
                string path = getenv("PATH");
                stringstream ss(path);
                string unique_path;

                while (getline(ss,unique_path, ':')) {

                    string full_path = unique_path + "/" + input;

                    if (access(full_path.c_str(), X_OK) == 0) {
                        cout << input << " is " << full_path << endl;
                        file_found = true;
                        break;
                    }

                }

                if (!file_found) {
                    cout << input << ": not found" << endl;
                }
        
            }

            return 0;
    }
}