//
// Created by derek on 3/24/2017.
//

#pragma once

#include <iostream>

/// A templated Stack storage mechanism
/// \tparam T The type of data to hold
template <typename T>
class Stack {
    /// The current index of the top item in the stack
    int top = -1;

    /// The size of the stack
    static const int size = 20;

    /// The underlying stack storage mechanism
    T values[size];

public:
    /*/// Pushes an item onto the top of the stack
    /// \param item The item to be pushed
    void push(T& item) {
        try {
            if (top < 20) {
                values[++top] = item;
            } else {
                throw -1;
            }
        } catch (int e) {
            std::cerr << "Stack overflow" << std::endl;
        }
    }*/

    /// Pushes an item onto the top of the stack by copying it
    /// \param item The item to be copied and pushed
    void push(T item) {
        try {
            if (top < 20) {
                values[++top] = item;
            } else {
                throw -1;
            }
        } catch (int e) {
            std::cerr << "Stack overflow" << std::endl;
        }
    }

    /// Pops the top item off of the stack
    /// \return The top item of the stack
    T pop() {
        return top > -1 ? values[top--] : throw -1;
    }

    /// Whether the stack is empty
    /// \return The state of the stack
    bool isEmpty() {
        return top < 0;
    }


    /// Gets the top item of the stack without removing it
    /// \return The top item of the stack
    const T* getTop() {
        return &values[top];
    }

    const int getTopIndex() {
        return top;
    }

    T operator[](int index) {
        return values[index];
    }
};
