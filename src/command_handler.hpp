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
#include <regex>

using namespace std;

namespace shell {

    static unordered_map<string, function<int(const string&)>> map_commands = {

        {"echo", &echo::execute}, 
        {"type", &type::execute}, 
        {"exit", &exit::execute},
        {"pwd", &pwd::execute},
        {"cd", &cd::execute},
    };

    string remove_whitespace(string& input) {
        // Space handling
        int index = 0;
        int start_index;
        size_t range;

        while (index < input.length()) {

            start_index = 0;
            range = 0;

            if (input[index] == ' ') {
                start_index = index;
                while (input[index + 1] == ' ') {
                    range += 1;
                    index += 1;
                }
            }

            if (range > 0) {
                input.erase(start_index, range);
            }

            index += 1;
        }

        return input;
    }

    string pattern_match_handling(string& input, regex pattern, string keyword) {

        string::const_iterator start = input.cbegin();
        smatch match;
        string result;
        
        
        while(regex_search(start, input.cend(), match, pattern)){
            if (match.prefix().length()) {
                string prefixed_string = match.prefix();
                result += remove_whitespace(prefixed_string);
            }

            result += match[1];

            string temp_suffix = match.suffix();
            
            if (keyword == "double" && temp_suffix.find('\"') == string::npos) {
                result += remove_whitespace(temp_suffix);
            }
            
            if (keyword == "single" && temp_suffix.find('\'') == string::npos) {
                result += remove_whitespace(temp_suffix);
            }
            
            start = match.suffix().first;
        }

        result = result.empty()? input : result;

        return result;
    }

    void handle_input(string& input) {

        string quote_sanitised;
        regex pattern_single_quote("'([^']*)'");
        regex pattern_double_quote("\"([^\"]*)\"");

        if (input.find('\"') != string::npos) {
            quote_sanitised = pattern_match_handling(input, pattern_double_quote, "double");
        }

        if (quote_sanitised.find('\'') != string::npos) {
            quote_sanitised = pattern_match_handling(quote_sanitised, pattern_single_quote, "single");
        } 

        if (quote_sanitised.empty()) {
            quote_sanitised += remove_whitespace(input);
        }

        input = quote_sanitised;
    }

    int execute(const string& command) {

        size_t index_first_space = command.find(" ");
        string extracted_command;
        string input;


        if (index_first_space != string::npos) {
            extracted_command = command.substr(0,index_first_space);
            input = command.substr(index_first_space + 1);
            handle_input(input);
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