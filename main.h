#ifndef MAIN_H
#define MAIN_H

#include <string>

// *****************************************************************************
// StackADT Interface
// *****************************************************************************
// This abstract base class defines the contract for a stack data structure.
// Every stack implementation (array based or linked list based) must provide
// definitions for these methods, as required by Part 1 of the lab.
template<typename T>
class StackADT {
public:
    // Returns true if the stack is empty.
    virtual bool isEmpty() const = 0;
    
    // Pushes a value onto the stack.
    virtual void push(const T & value) = 0;
    
    // Returns (but does not remove) the top element.
    virtual T peek() const = 0;
    
    // Removes the top element from the stack. Returns false if the stack is empty.
    virtual bool pop() = 0;
};

// *****************************************************************************
// Global Constants
// *****************************************************************************
constexpr int MIN_ARRAY_SIZE = 64;

// *****************************************************************************
// ArrayStack Declaration
// *****************************************************************************
// Implements the StackADT interface using a fixed-size array. This is the
// array-based stack required in Part 1.
template<typename T, int N>
class ArrayStack : public StackADT<T> {
private:
    int topIndex;   // Index of the top element (-1 indicates empty).
    T array[N] {};  // Fixed-size array to store elements.
public:
    ArrayStack();
    bool isEmpty() const override;
    void push(const T & value) override;
    T peek() const override;
    bool pop() override;
};

// *****************************************************************************
// Forward Declaration for Node
// *****************************************************************************
template<typename T>
class Node;

// *****************************************************************************
// ListStack Declaration
// *****************************************************************************
// Implements the StackADT interface using a singly linked list. This is the
// linked-list based stack required in Part 1. It includes a destructor,
// a copy constructor, and a move constructor to manage dynamic memory.
template<typename T>
class ListStack : public StackADT<T> {
private:
    Node<T>* top; // Pointer to the top node in the linked list.
public:
    ListStack();
    ~ListStack();
    ListStack(const ListStack & other);         // Copy constructor.
    ListStack(ListStack && other) noexcept;       // Move constructor.
    bool isEmpty() const override;
    void push(const T & value) override;
    T peek() const override;
    bool pop() override;
};

// *****************************************************************************
// Warmup and Algorithm Function Prototypes (Parts 2 and 3)
// *****************************************************************************

// (A) Matching Curly Brace Detector - verifies that every '{' has a matching '}'.
bool areCurleyBracesMatched(const std::string & inputString);

// (B) Palindrome Detector - checks if a string reads the same forward and backward.
bool isPalindrome(const std::string & inputString);

// (C) String Reverser - returns the reverse of the given string using stack's LIFO.
std::string reversedString(const std::string & inputString);

// (D) Infix to Postfix Converter - converts an infix expression (e.g., a+b*c)
//     into postfix notation (e.g., abc*+), observing operator precedence.
std::string infixToPostFix(const std::string & infix);

// *****************************************************************************
// Unit Test Function Prototypes
// *****************************************************************************
void testArrayStack();
void testListStack();
void testAreCurleyBracesMatched();
void testIsPalindrome();
void testReversedString();
void testInfixToPostFix();

#endif // MAIN_H
