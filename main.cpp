// Using C++20
#include "main.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include <stdexcept>
#include <vector>

using namespace std;

// =============================================================================
// ArrayStack Implementation (Part 1: Array Based Stack)
// =============================================================================

// Constructor: Initializes an empty ArrayStack.
// Sets topIndex to -1 (an empty stack) and ensures the array size meets minimum.
template<typename T, int N>
ArrayStack<T, N>::ArrayStack() : topIndex(-1) {
    static_assert(N >= MIN_ARRAY_SIZE, "Array size must be at least MIN_ARRAY_SIZE.");
}

// isEmpty: Returns true when no elements are in the stack.
template<typename T, int N>
bool ArrayStack<T, N>::isEmpty() const {
    return topIndex == -1; // An empty stack has topIndex of -1.
}

// push: Adds a new element to the top of the stack.
// Checks for overflow before inserting the element.
template<typename T, int N>
void ArrayStack<T, N>::push(const T & value) {
    // When topIndex is N-1, the stack is full.
    if(topIndex == N - 1) {
        throw std::length_error("Max array exceeded.");
    }
    array[++topIndex] = value; // Increment topIndex and assign the value.
}

// peek: Returns the element at the top of the stack without removing it.
template<typename T, int N>
T ArrayStack<T, N>::peek() const {
    if(isEmpty()) {
        throw std::logic_error("Peek on empty ArrayStack.");
    }
    return array[topIndex];
}

// pop: Removes the top element from the stack.
// Returns false if the stack is empty; otherwise, returns true.
template<typename T, int N>
bool ArrayStack<T, N>::pop() {
    if(isEmpty()) {
        return false;
    }
    topIndex--;  // Decrement topIndex to "remove" the top element.
    return true;
}

// -----------------------------------------------------------------------------

// Unit test for ArrayStack.
// Ensures that all basic operations (push, pop, peek, isEmpty) work as specified.
void testArrayStack() {
    ArrayStack<int, MIN_ARRAY_SIZE> stack0;
    assert(stack0.isEmpty());             // Initially, the stack should be empty.
    stack0.push(10);                      // Push 10.
    assert(stack0.peek() == 10);           // Top element should be 10.
    stack0.push(20);                      // Push 20.
    assert(stack0.peek() == 20);           // Top element should now be 20.
    assert(stack0.pop());                 // Pop the top element (20).
    assert(stack0.peek() == 10);           // Top element should revert to 10.
    assert(stack0.pop());                 // Pop the remaining element (10).
    assert(stack0.isEmpty());             // Stack should be empty after pops.
}

// =============================================================================
// Node and ListStack Implementation (Part 1: Linked-List Based Stack)
// =============================================================================

// ----------------------
// Node Class Definition
// ----------------------
// Represents an individual node in the linked list stack.
template<typename T>
class Node {
private:
    T value;       // Data stored in the node.
    Node* next;    // Pointer to the next node.
public:
    // Constructors.
    Node(T value) : value(value), next(nullptr) {}
    Node(T value, Node* next) : value(value), next(next) {}

    // Accessors.
    T getValue() const { return value; }
    Node* getNext() const { return next; }

    // Mutators.
    void setNext(Node* n) { next = n; }
    void setValue(const T & v) { value = v; }
};

// ----------------------
// ListStack Implementation
// ----------------------

// Constructor: Initializes an empty ListStack.
template<typename T>
ListStack<T>::ListStack() : top(nullptr) {}

// Destructor: Frees all nodes in the linked list to avoid memory leaks.
template<typename T>
ListStack<T>::~ListStack() {
    while(pop()) {}  // Keep popping until the stack is empty.
}

// Copy Constructor: Creates a deep copy of another ListStack.
// To preserve the order (with the same top), we first copy the values into a vector
// and then push them in reverse order.
template<typename T>
ListStack<T>::ListStack(const ListStack & other) : top(nullptr) {
    if(other.top == nullptr) return; // If other is empty, nothing to copy.
    
    vector<T> values;
    // Traverse the original stack from top to bottom.
    for(Node<T>* current = other.top; current != nullptr; current = current->getNext()) {
        values.push_back(current->getValue());
    }
    // Push elements into the new stack so that the top remains the same.
    for(auto it = values.rbegin(); it != values.rend(); ++it) {
        push(*it);
    }
}

// Move Constructor: Transfers ownership from the other ListStack to this one.
// The other stack is left empty (i.e., its top pointer becomes nullptr).
template<typename T>
ListStack<T>::ListStack(ListStack && other) noexcept : top(other.top) {
    other.top = nullptr;
}

// isEmpty: Returns true if the ListStack is empty (i.e., top is nullptr).
template<typename T>
bool ListStack<T>::isEmpty() const {
    return top == nullptr;
}

// push: Inserts a new value at the top of the ListStack.
// Creates a new Node that points to the current top.
template<typename T>
void ListStack<T>::push(const T & value) {
    Node<T>* newNode = new Node<T>(value, top);
    top = newNode;
}

// peek: Returns the value of the top element without removing it.
template<typename T>
T ListStack<T>::peek() const {
    if(isEmpty()) {
        throw std::logic_error("Peek on empty ListStack.");
    }
    return top->getValue();
}

// pop: Removes the top element from the ListStack and frees its memory.
template<typename T>
bool ListStack<T>::pop() {
    if(isEmpty()) {
        return false;
    }
    Node<T>* temp = top;
    top = top->getNext();
    delete temp;
    return true;
}

// -----------------------------------------------------------------------------

// Unit test for ListStack.
// Checks push, pop, peek as well as the copy and move constructors.
void testListStack() {
    ListStack<int> stack0;
    assert(stack0.isEmpty());
    stack0.push(10);
    assert(stack0.peek() == 10);
    stack0.push(20);
    assert(stack0.peek() == 20);
    assert(stack0.pop());
    assert(stack0.peek() == 10);
    assert(stack0.pop());
    assert(stack0.isEmpty());

    // Test copy constructor.
    stack0.push(1);
    stack0.push(2);
    stack0.push(3);
    ListStack<int> stack1(stack0);
    assert(!stack0.isEmpty());
    assert(stack0.peek() == 3);
    assert(!stack1.isEmpty());
    assert(stack1.peek() == 3);

    // Test move constructor.
    ListStack<int> stack2(std::move(stack0));
    assert(stack0.isEmpty());
    assert(!stack2.isEmpty());
    assert(stack2.peek() == 3);
}

// =============================================================================
// Warmup Functions Implementation (Part 2)
// =============================================================================

// -----------------------------------------------------------------------------
// (A) Matching Curly Brace Detector
// -----------------------------------------------------------------------------
/*
    This function scans the input string and uses a stack (ArrayStack<char>) to
    ensure that every opening curly brace '{' has a corresponding closing brace '}'.
    It maps directly to Part 2A of the lab instructions.
*/
bool areCurleyBracesMatched(const string & inputString) {
    ArrayStack<char, MIN_ARRAY_SIZE> stack;
    for(char ch : inputString) {
        if(ch == '{') {
            stack.push(ch);  // Push any opening brace.
        } else if(ch == '}') {
            // For a closing brace, ensure there is a matching opening brace.
            if(stack.isEmpty()) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.isEmpty(); // If the stack is empty, all braces are matched.
}

// Unit test for Matching Curly Brace Detector.
void testAreCurleyBracesMatched() {
    assert(areCurleyBracesMatched(""));           // Empty string.
    assert(areCurleyBracesMatched("{}"));         // Simple match.
    assert(areCurleyBracesMatched("a{bc}d"));       // Embedded braces.
    assert(!areCurleyBracesMatched("{"));          // Unmatched opening brace.
    assert(!areCurleyBracesMatched("}"));          // Unmatched closing brace.
    assert(!areCurleyBracesMatched("a{b{c}"));       // Incomplete matching.
}

// -----------------------------------------------------------------------------
// (B) Palindrome Detector
// -----------------------------------------------------------------------------
/*
    This function uses a stack (ArrayStack<char>) to reverse the input string and
    then compares it with the original to determine if it is a palindrome.
    This directly addresses Part 2B.
*/
bool isPalindrome(const string & inputString) {
    ArrayStack<char, MIN_ARRAY_SIZE> stack;
    for(char ch : inputString) {
        stack.push(ch);
    }
    string reversed;
    while(!stack.isEmpty()) {
        reversed.push_back(stack.peek());
        stack.pop();
    }
    return inputString == reversed;
}

// Unit test for Palindrome Detector.
void testIsPalindrome() {
    assert(isPalindrome(""));
    assert(isPalindrome("a"));
    assert(isPalindrome("aa"));
    assert(isPalindrome("aba"));
    assert(isPalindrome("abba"));
    assert(!isPalindrome("ab"));
    assert(!isPalindrome("abaa"));
}

// -----------------------------------------------------------------------------
// (C) String Reverser
// -----------------------------------------------------------------------------
/*
    This function returns the reverse of the input string using the LIFO
    property of a stack. It maps directly to Part 2C.
*/
string reversedString(const string & inputString) {
    ArrayStack<char, MIN_ARRAY_SIZE> stack;
    for(char ch : inputString) {
        stack.push(ch);
    }
    string reversed;
    while(!stack.isEmpty()) {
        reversed.push_back(stack.peek());
        stack.pop();
    }
    return reversed;
}

// Unit test for String Reverser.
void testReversedString() {
    assert(reversedString("").empty());
    assert(reversedString("a") == "a");
    assert(reversedString("ab") == "ba");
    assert(reversedString("abc") == "cba");
}

// =============================================================================
// Infix to Postfix Converter Implementation (Part 3)
// =============================================================================

/*
    This function converts an infix expression (with operands as lower-case letters
    and operators +, -, *, /) into a postfix expression. It follows the standard
    algorithm: operands are output immediately, and operators are pushed onto a
    stack with proper precedence handling. Parentheses are used to override precedence.
*/
string infixToPostFix(const string & infix) {
    ArrayStack<char, MIN_ARRAY_SIZE> stack;  // Stack to hold operators.
    string postfix;  // Output postfix expression.

    for(char ch : infix) {
        if(isalpha(ch)) {  // Operand detected.
            postfix.push_back(ch);
        } else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Operator detected. Pop from the stack while the operator at the top has
            // greater or equal precedence and is not a '('.
            while(!stack.isEmpty() && stack.peek() != '(' && 
                  ((stack.peek() == '*' || stack.peek() == '/') || 
                   ((stack.peek() == '+' || stack.peek() == '-') && (ch == '+' || ch == '-')))) {
                postfix.push_back(stack.peek());
                stack.pop();
            }
            stack.push(ch);
        } else if(ch == '(') {
            stack.push(ch);
        } else if(ch == ')') {
            // Pop until the matching '(' is found.
            while(!stack.isEmpty() && stack.peek() != '(') {
                postfix.push_back(stack.peek());
                stack.pop();
            }
            if(!stack.isEmpty() && stack.peek() == '(') {
                stack.pop();  // Remove the '('.
            }
        }
    }
    // Append any remaining operators.
    while(!stack.isEmpty()) {
        postfix.push_back(stack.peek());
        stack.pop();
    }
    return postfix;
}

// Unit test for Infix to Postfix Converter.
void testInfixToPostFix() {
    assert(infixToPostFix("").empty());
    assert(infixToPostFix("a") == "a");
    assert(infixToPostFix("a+b") == "ab+");
    assert(infixToPostFix("a*b") == "ab*");
    assert(infixToPostFix("a+b*c") == "abc*+");
    assert(infixToPostFix("a+(b*c)") == "abc*+");
    assert(infixToPostFix("(a+(b*c))") == "abc*+");
    assert(infixToPostFix("(a+b)*c") == "ab+c*");
    assert(infixToPostFix("((a+b)*c)") == "ab+c*");
    assert(infixToPostFix("a*b+c") == "ab*c+");
    assert(infixToPostFix("(a*b)+c") == "ab*c+");
    assert(infixToPostFix("((a*b)+c)") == "ab*c+");
}

// =============================================================================
// Main Function
// =============================================================================

/*
    The main() function calls each unit test to verify that all components of the lab
    (Parts 1-3) are correctly implemented. Passing all tests confirms that:
      - Both stack implementations work correctly.
      - The warmup algorithms (matching braces, palindrome, reverse string) work.
      - The infix to postfix conversion is properly implemented.
    For Part 4 (Eight Queens), the code would be provided separately or as additional files.
*/
int main() {
    testArrayStack();             // Test the array-based stack.
    testListStack();              // Test the linked-list based stack (including copy/move).
    testAreCurleyBracesMatched(); // Test the matching curly brace detector.
    testIsPalindrome();           // Test the palindrome detector.
    testReversedString();         // Test the string reverser.
    testInfixToPostFix();         // Test the infix-to-postfix converter.
    
    cout << "All tests passed successfully." << endl;
    return 0;
}
