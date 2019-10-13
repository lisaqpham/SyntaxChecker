#include <iostream>

using namespace std;

template <typename T>
class GenStack { //stands for Generic Stack
  public:
    GenStack(); //constructor
    GenStack(int maxSize); //overloaded constructor
    ~GenStack(); //destructor

    void push(T d);
    T pop();
    T peek(); //AKA top()

    bool isFull();
    bool isEmpty();

    int size;
    int top;

    T *myArray; //* is a pointer
};

template <typename T>
GenStack<T>::GenStack() {//default constructor
  //initialization of default values
  myArray = new T[128];
  size = 128;
  top = -1; //index
}

template <typename T>
GenStack<T>::GenStack(int maxSize) {
  myArray = new T[maxSize];
  size = maxSize;
  top = -1;
}

template <typename T>
GenStack<T>::~GenStack() {
  delete[] myArray;
}

template <typename T>
void GenStack<T>::push(T d) {
  //need to check error/boundary check
  //this is your job
  myArray[++top] = d; //adds one to top then pushes
}

template <typename T>
T GenStack<T>::pop() {
  if (isEmpty()) {
    throw;
  } else {
    return myArray[top--]; //returns top value then subtracts one from top
  }
}

template <typename T>
T GenStack<T>::peek() {
  //check if empty
  return myArray[top];
}

template <typename T>
bool GenStack<T>::isFull(){
  return (top == size-1);
}

template <typename T>
bool GenStack<T>::isEmpty() {
  return (top == -1);
}
