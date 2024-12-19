#include <iostream>
#include <cassert>
#include "pointer.h"

class TestClass {
public:
    TestClass() {
        std::cout << "TestClass created.\n";
    }
    ~TestClass() {
        std::cout << "TestClass destroyed.\n";
    }
    void greet() const {
        std::cout << "Hello from TestClass.\n";
    }
};

void testDefaultConstructor() {
    std::cout << "Testing default constructor...\n";
    SmartPointer<TestClass> sp;
    assert(sp == nullptr && "Default constructor test failed.");
}

void testParameterizedConstructor() {
    std::cout << "Testing parameterized constructor...\n";
    SmartPointer<TestClass> sp(new TestClass());
    assert(sp != nullptr && "Parameterized constructor test failed.");
    sp->greet();
}

void testCopySemantics() {
    std::cout << "Testing copy constructor and assignment...\n";
    SmartPointer<TestClass> original(new TestClass());
    original->greet();
    
    SmartPointer<TestClass> copy = original;  // This should now create a new TestClass instance
    assert(copy != nullptr && "Copy constructor test failed.");
    copy->greet(); // This should work as a deep copy has been made

    SmartPointer<TestClass> assigned;
    assigned = original; // This should also perform deep copy
    assert(assigned != nullptr && "Copy assignment test failed.");
    assigned->greet();
}

void testMoveSemantics() {
    std::cout << "Testing move constructor and move assignment...\n";
    SmartPointer<TestClass> movedFrom(new TestClass());
    SmartPointer<TestClass> movedTo = std::move(movedFrom);
    assert(movedTo != nullptr && movedFrom == nullptr && "Move semantics test failed.");
    movedTo->greet();

    SmartPointer<TestClass> movedAssigned;
    movedAssigned = std::move(movedTo);
    assert(movedAssigned != nullptr && movedTo == nullptr && "Move assignment test failed.");
    movedAssigned->greet();
}

void testDestruction() {
    std::cout << "Testing destruction...\n";
    {
        SmartPointer<TestClass> sp(new TestClass());
    } // Destructor should be invoked here
    std::cout << "SmartPointer should be destroyed now.\n";
}

void testNullPointerAccess() {
    std::cout << "Testing access through null pointer...\n";
    SmartPointer<TestClass> sp;
    try {
        sp->greet();  // Should handle or throw an exception
    } catch (...) {
        std::cout << "Exception caught from null pointer access.\n";
    }
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopySemantics();
    testMoveSemantics();
    testDestruction();
    testNullPointerAccess();

    std::cout << "All tests completed.\n";
    return 0;
}
