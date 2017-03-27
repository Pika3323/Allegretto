//
// Created by derek on 3/24/2017.
//

#pragma once

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
    /// Pushes an item onto the top of the stack
    /// \param item The item to be pushed
    void push(T& item) {
        values[++top] = item;
    }

    /// Pushes an item onto the top of the stack by copying it
    /// \param item The item to be copied and pushed
    void push(T item) {
        values[++top] = item;
    }

    /// Pops the top item off of the stack
    /// \return The top item of the stack
    T pop() {
        return top > -1 ? values[top--] : T();
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
};
