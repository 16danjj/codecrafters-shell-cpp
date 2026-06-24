#pragma once

#include <iostream>
#include <string>
#include "echo.hpp"
#include "type.hpp"
#include "exit.hpp"
#include "pwd.hpp"
#include <unordered_map>
#include <functional>

using namespace std;

namespace shell {

    static unordered_map<string, function<int(const string&)>> map_commands = {

        {"echo", &echo::execute}, 
        {"type", &type::execute}, 
        {"exit", &exit::execute},
        {"pwd", &pwd::execute},
    };

    int execute(const string& command) {
        size_t index_first_space = command.find(" ");
        string extracted_command;
        string input;
        bool file_found = false;

        if (index_first_space != string::npos) {
            extracted_command = command.substr(0,index_first_space);
            input = command.substr(index_first_space + 1);

        } else {
            extracted_command = command;
        }


        if (map_commands.find(extracted_command) != map_commands.end()) {
            return map_commands[extracted_command](input);
        } else {
            // executable with arguments related logic
            stringstream s1(command);
            string token;

            vector<string> temp_storage;

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

            // This currently serves as our catch-all for all other cases 
            if (!file_found) {
                cout << command << ": command not found" << endl;
            }           
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