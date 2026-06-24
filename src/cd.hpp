#pragma once

#include <iostream>
#include <string>

#include <unistd.h>


using namespace std;

namespace shell::cd {

    int execute(const string& input){

        int result;

        if (input == "~") {

            string path = getenv("HOME");
            chdir(path.c_str());
            return 0;
        }

        result = chdir(input.c_str());

        if (result != 0) {
            cout << "cd: " << input << ": No such file or directory" << endl;
        }

        
        return 0;
    }
}