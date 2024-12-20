#include <iostream>
#include <vector>
#include <cstdlib>  // for rand and srand (optional, if we decide to do random tests)
#include <ctime>    // for time (optional)
#include "LinkedList.h" // Include your linked list header

int main() {
    LinkedList<int> list;

    // Test 1: Insert into empty list
    std::cout << "Test 1: Inserting into empty list..." << std::endl;
    list.insert(10);
    std::cout << "Expected: 10" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 2: Insert multiple elements
    std::cout << "\nTest 2: Inserting multiple elements (20, 30, 40)..." << std::endl;
    list.insert(20);
    list.insert(30);
    list.insert(40);
    std::cout << "Expected: 10 20 30 40" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 3: Remove head element
    std::cout << "\nTest 3: Removing head element (10)..." << std::endl;
    list.remove(10);
    std::cout << "Expected: 20 30 40" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 4: Remove middle element (30)
    std::cout << "\nTest 4: Removing middle element (30)..." << std::endl;
    list.remove(30);
    std::cout << "Expected: 20 40" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 5: Remove last element (40)
    std::cout << "\nTest 5: Removing last element (40)..." << std::endl;
    list.remove(40);
    std::cout << "Expected: 20" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 6: Remove non-existent element (999)
    std::cout << "\nTest 6: Removing non-existent element (999)..." << std::endl;
    list.remove(999);
    std::cout << "Expected: 20 (unchanged)" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 7: Remove the only element left (20), making the list empty
    std::cout << "\nTest 7: Removing the only element (20)..." << std::endl;
    list.remove(20);
    std::cout << "Expected: (empty)" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 8: Remove from empty list
    std::cout << "\nTest 8: Removing from empty list (attempt to remove 10)..." << std::endl;
    list.remove(10); // Should do nothing gracefully
    std::cout << "Expected: (empty)" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 9: Insert multiple elements again
    std::cout << "\nTest 9: Reinserting elements (1,2,3,4,5)..." << std::endl;
    for (int i = 1; i <= 5; ++i) {
        list.insert(i);
    }
    std::cout << "Expected: 1 2 3 4 5" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 10: Remove multiple elements repeatedly
    std::cout << "\nTest 10: Removing multiple elements repeatedly (2, then 4)..." << std::endl;
    list.remove(2);
    list.remove(4);
    std::cout << "Expected: 1 3 5" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 11: Insert duplicates and remove one occurrence
    std::cout << "\nTest 11: Insert duplicates (3,3,3) and remove one occurrence..." << std::endl;
    list.insert(3);
    list.insert(3);
    list.insert(3);
    // Now list: 1 3 5 3 3 3
    std::cout << "After insertion: Expected: 1 3 5 3 3 3" << std::endl;
    std::cout << "Got:                       "; list.display();
    list.remove(3); // Remove the first occurrence from left to right
    std::cout << "After removing one '3': Expected: 1 5 3 3 3" << std::endl;
    std::cout << "Got:                              "; list.display();

    // Test 12: Remove all instances of a value by calling remove multiple times
    std::cout << "\nTest 12: Removing '3' multiple times until gone..." << std::endl;
    list.remove(3); // removes first 3 from the remaining set
    list.remove(3);
    list.remove(3); // now all 3's should be gone
    std::cout << "Expected: 1 5" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 13: Large insertion test (optional: stress test)
    std::cout << "\nTest 13: Large insertion test..." << std::endl;
    // Clear the list first
    list.remove(1);
    list.remove(5);
    // Now list should be empty
    std::cout << "After clearing, expected: (empty)" << std::endl;
    std::cout << "Got:                     "; list.display();

    // Insert a large number of elements
    for (int i = 0; i < 10; ++i) {
        list.insert(i);
    }
    std::cout << "Expected: 0 1 2 3 4 5 6 7 8 9" << std::endl;
    std::cout << "Got:      "; list.display();

    // Random removals
    std::cout << "\nRemoving some values: (removing 0, 9, 5)" << std::endl;
    list.remove(0);
    list.remove(9);
    list.remove(5);
    std::cout << "Expected: 1 2 3 4 6 7 8" << std::endl;
    std::cout << "Got:      "; list.display();

    // Test 14: Remove until empty again
    std::cout << "\nTest 14: Removing all remaining elements..." << std::endl;
    for (int v : {1,2,3,4,6,7,8}) {
        list.remove(v);
    }
    std::cout << "Expected: (empty)" << std::endl;
    std::cout << "Got:      "; list.display();

    // Final message
    std::cout << "\nAll rigorous tests completed." << std::endl;

    return 0;
}
