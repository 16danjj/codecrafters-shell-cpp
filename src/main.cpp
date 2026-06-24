#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <unistd.h>
#include <vector>
#include "command_handler.hpp"
using namespace std;

int main() {
  // Flush after every cout / std:cerr
  cout << unitbuf;
  cerr << unitbuf;

  shell::repl();
}
