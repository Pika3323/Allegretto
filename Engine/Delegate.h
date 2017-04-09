//
// Created by derek on 3/27/2017.
//

#pragma once

/**
 * Empty class to use for type erasure
 */
class GameObject;

/**
 * A class used to leverage polymorphism into storing pointers to methods of any type of object.
 * Classified as an extreme "hack" by some people. Called useless by other naive people. But man.. is it useful.
 * @tparam MethodType The method signature of the methods to delegate
 */
template<typename MethodType>
class Delegate {
protected:
    /**
     * The object which the method should be called on. Should be the same type as the method object.
     */
    GameObject* object;

    /**
     * The method to be called
     */
    MethodType method;

public:
    /**
     * Constructor
     * @tparam T Type
     * @param obj Object
     * @param mthd Pointer to method
     */
    template <typename T, typename R>
    Delegate(T* obj, R mthd) : object((GameObject*) obj), method((MethodType) mthd) {}

    Delegate() {}

    /**
     * Calls the method on the set object
     */
    //virtual void Call() = 0;

    /**
     * Calls the method on the set object
     * @tparam Args The types of arguments to pass to the method (can be automatically deduced by the compiler)
     * @param args Any arguments that should be passed into the method
     */
    template<typename... Args>
    void Call(Args... args) {
        (object->*method)(args...);
    }

    /**
     * Gets the object bound to this delegate
     * @tparam T The type of the object that should be gotten
     * @return The type of object to return
     */
    template<typename T>
    T* GetObject() {
        return (T*) object;
    }
};