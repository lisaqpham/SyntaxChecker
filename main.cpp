#include "GenStack.cpp"
#include <iostream>
#include <fstream>

using namespace std;
char nextChar;
bool repeat = true;
int lines;
string tester;
string newFile;
string answer;
ifstream infile;

void inputFile() {
  cin >> newFile;
  infile.open(newFile);
  if (!infile) {
    cout << "Cannot open input file. Please try again" << endl;
    inputFile();
  }
}

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

int main (int argc, char **argv) {
  GenStack<char> myStack(10);
  cout << "Delimiter Checker" << endl;
  cout << "--------------------" << endl;
  cout << "Please input your file name: ";
  inputFile();

  while (repeat) {
    while (infile.get(nextChar)) {
      if (nextChar == '\n') {
        lines++;
      } else if (nextChar == '{' || nextChar == '[' || nextChar == '(') {
        myStack.push(nextChar);
      } else if (nextChar == '}' || nextChar == ']' || nextChar == ')') {
        if (delimiterPair(nextChar) == myStack.peek()) {
          myStack.pop();
        } else {
          cout << "Line " << lines + 1 << ": expected " << delimiterPair(myStack.peek()) << ", found " << nextChar << endl;
          return 1;
        }
      }
    }

    if (!myStack.isEmpty()) {
      cout << "Reached end of file: missing " << delimiterPair(myStack.peek()) << endl;
      return 1;
    } else {
      infile.close();
      cout << "All delimiter syntax is correct." << endl;
      cout << "Would you like to check another file? (y/n)" << endl;
      cin >> answer;
      if (answer == "yes" || answer == "y") {
        cout << "Please input your file name: ";
        inputFile();
      } else {
        repeat = false;
        return 0;
      }
    }
  }
}
