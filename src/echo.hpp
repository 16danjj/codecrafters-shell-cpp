#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace shell::echo {

    int execute(const string& input){
        cout << input << endl;
        return 0;
    }
}