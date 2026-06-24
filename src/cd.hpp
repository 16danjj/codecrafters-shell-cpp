#pragma once

#include <iostream>
#include <string>

#include <unistd.h>


using namespace std;

namespace shell::cd {

    int execute(const string& input){

        int result;

        if (input.rfind("/", 0) == 0)  { // absolute path

            result = chdir(input.c_str());

            if (result != 0) {
                cout << "cd: " << input << ": No such file or directory" << endl;
            }
        }
        
        return 0;
    }
}