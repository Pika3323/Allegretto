#pragma once

/**
 * The base class of all Delegates
 * Allows for arrays of generic Delegates and such
 * Contains the object reference for delegates to call from
 */
class DelegateBase {
protected:
    /**
     * Base class of any object that is going to be used with a delegate.
     * Empty non-templated class to allow for more generic storage
     */
    class DelegateObjectBase {};

    /**
     * The object which the method should be called on. Should be the same type as the method object.
     */
    DelegateObjectBase* object;

public:

    DelegateBase(DelegateObjectBase* object) : object(object) {}

    /**
     * Gets the object bound to this delegate
     * @tparam T The type of the object that should be gotten
     * @return The type of object to return
     */
    template<typename T>
    T* GetObject() {
        return (T*) object;
    }

    virtual ~DelegateBase() {}
};

/**
 * A class used to leverage polymorphism into storing pointers to methods of any type of object.
 * Classified as an extreme "hack" by some people. Called useless by other naive people. But man.. is it useful.
 * @tparam ReturnType The return type of the delegated method
 * @tparam Args List of arguments that get passed on to the delegated method
 */
template<typename ReturnType, typename... Args>
class Delegate : public DelegateBase {

protected:
    /**
     * The method that is being delegated
     * Holds a reference to the method that can be called later on using the DelegateBase's object reference
     */
    ReturnType(DelegateObjectBase::*method)(Args...);

public:
    /**
     * Constructor
     * @tparam T Type
     * @param obj Object
     * @param methodVar Pointer to method
     */
    template <typename T, typename R>
    Delegate(T* obj, R methodVar) : method((ReturnType(DelegateObjectBase::*)(Args...)) methodVar), DelegateBase((DelegateObjectBase*) obj) {}

    /**
     * Calls the method on the set object
     * @param args Any arguments that should be passed into the method
     */
    void Call(Args... args) {
        (object->*method)(args...);
    }
};