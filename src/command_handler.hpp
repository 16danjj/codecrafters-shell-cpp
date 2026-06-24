#pragma once

#include <iostream>
#include <string>
#include "echo.hpp"
#include "type.hpp"
#include "exit.hpp"
#include "pwd.hpp"
#include "cd.hpp"
#include "find_executable.hpp"
#include <unordered_map>
#include <functional>

using namespace std;

namespace shell {

    static unordered_map<string, function<int(const string&)>> map_commands = {

        {"echo", &echo::execute}, 
        {"type", &type::execute}, 
        {"exit", &exit::execute},
        {"pwd", &pwd::execute},
        {"cd", &cd::execute},
    };

    int execute(const string& command) {
        size_t index_first_space = command.find(" ");
        string extracted_command;
        string input;


        if (index_first_space != string::npos) {
            extracted_command = command.substr(0,index_first_space);
            input = command.substr(index_first_space + 1);

        } else {
            extracted_command = command;
        }


        if (map_commands.find(extracted_command) != map_commands.end()) {
            return map_commands[extracted_command](input);
        } else if (find_executable::file_find(command)) {
            system(command.c_str());
            return 0;
        } else {
            cout << command << ": command not found" << endl;
            return 0;
        }
    }

    void repl() {

        while (true) {
            cout << "$ ";
            string command;
            getline(cin, command);
            int success = execute(command);

            if (success == -1) {
                break;
            }
        }
    }
}