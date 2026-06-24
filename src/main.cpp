#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <unistd.h>
#include <vector>
using namespace std;

int main() {
  // Flush after every cout / std:cerr
  cout << unitbuf;
  cerr << unitbuf;

  string command;

  
  while (1) {
    cout << "$ ";


    getline(cin, command);
    bool file_found = false;
    
    if (command == "exit"){
      break;
    } else if (command.substr(0,5) == "type ") {
      if (command.substr(5) == "echo" || command.substr(5) == "exit" || command.substr(5) == "type") {
        cout << command.substr(5) << " is a shell builtin" << endl;
      } else {

        string path = getenv("PATH");
        stringstream ss(path);
        string unique_path;


        while (getline(ss,unique_path, ':')) {

          string full_path = unique_path + "/" + command.substr(5);

          if (access(full_path.c_str(), X_OK) == 0) {
            cout << command.substr(5) << " is " << full_path << endl;
            file_found = true;
            break;
          }

        }

        if (!file_found) {
          cout << command.substr(5) << ": not found" << endl;
        }
        
      }
    }
    
    else if (command.substr(0,5) == "echo ") {
      cout << command.substr(5) << endl;
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
            //system(command.c_str());
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

}
