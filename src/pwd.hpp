#pragma once

#include <iostream>
#include <string>
#include <unistd.h>


using namespace std;

namespace shell::pwd {

    char buffer[256];

    int execute(const string& input){
        cout << getcwd(buffer, sizeof(buffer)) << endl;
        return 0;
    }
}