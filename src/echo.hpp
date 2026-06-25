#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace shell::echo {

    int execute(const string& input){
        cout << input << endl;
        return 0;
    }
}