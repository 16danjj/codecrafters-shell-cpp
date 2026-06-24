#pragma once

#include <iostream>
#include <string>
#include <echo.hpp>
#include <type.hpp>
#include <exit.hpp>

using namespace std;

namespace shell {

    static unordered_map<string, function<int(const string&)>> map_commands = {

        {"echo", &echo::execute}, 
        {"type", &type::execute}, 
        {"exit", &exit::execute},
    };

    int execute(const string& command) {

    }

    void repl(const string& command) {

        while (true) {
            int success = execute(command);

            if (success == -1) {
                break;
            }
        }
    }
}