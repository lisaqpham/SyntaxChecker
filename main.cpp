#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

// global variables
char nextChar;
bool repeat = true;
int lines;
string tester;
string newFile;
string answer;
ifstream infile;

// recursive input file method
void inputFile() {
  cout << "Please input your file name: ";
  cin >> newFile;
  infile.open(newFile);
  //checks if file can be opened
  if (!infile) {
    cout << "Cannot open input file. Please try again" << endl;
    inputFile();
  }
}

// finds the corresponding delimeter
char delimiterPair(char delim) {
  if (delim == '}') {
    return '{';
  } else if (delim == ')') {
    return '(';
  } else if (delim == ']') {
    return '[';
  } else if (delim == '{') {
    return '}';
  } else if (delim == '(') {
    return ')';
  } else if (delim == '[') {
    return ']';
  } else {
    cout << "Error: Unexpected Delimiter";
  }
}

// main method
int main (int argc, char **argv) {
  // checks if the user used too many arguments
  if (argc > 2) {
    cout << "Error: Too many terminal arguments" << endl;
    return 0;
  }

  // declares a generic stack of 10
  GenStack<char> myStack(10);
  cout << "Delimiter Checker" << endl;
  cout << "--------------------" << endl;
  infile.open(argv[1]); // opens the file given
  if (!infile) { //checks if file can be opened
    cout << "Cannot open input file. Please try again" << endl;
    inputFile();
  }

  // loop for multiple files
  while (repeat) {
    while (infile.get(nextChar)) {
      if (nextChar == '\n') { // counts lines to specify in case of an error
        lines++;
      } else if (nextChar == '{' || nextChar == '[' || nextChar == '(') { // only pushes beginning delimiter
        myStack.push(nextChar);
      } else if (nextChar == '}' || nextChar == ']' || nextChar == ')') { // checks ending delimeter with beginning one
        if (delimiterPair(nextChar) == myStack.peek()) {
          myStack.pop(); // if the set is complete, then pop the delimiter from the stack
        } else { // Error message
          cout << "Line " << lines + 1 << ": expected " << delimiterPair(myStack.peek()) << ", found " << nextChar << endl;
          return 1;
        }
      }
    }

    // missing ending delimiter error
    if (!myStack.isEmpty()) {
      cout << "Reached end of file: missing " << delimiterPair(myStack.peek()) << endl;
      return 1;
    } else {
      infile.close();
      cout << "All delimiter syntax is correct." << endl;
      cout << "Would you like to check another file? (y/n)" << endl; // loop repeats
      cin >> answer;
      if (answer == "yes" || answer == "y") {
        inputFile();
      } else {
        repeat = false; //exit loop
        return 0;
      }
    }
  }
}
