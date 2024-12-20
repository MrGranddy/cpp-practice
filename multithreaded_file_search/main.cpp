#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

#include "search.h"

// Utility: A function to check if all expected files are present in results
bool containsAll(const std::vector<std::string>& results, const std::vector<std::string>& expected) {
    for (const auto& file : expected) {
        if (std::find(results.begin(), results.end(), file) == results.end()) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Setup: You'll need to create a test directory structure on your machine:
    // Suppose you have a directory structure like this:
    //
    // test_dir/
    // ├─ file1.txt
    // ├─ file2.txt
    // ├─ notes.md
    // ├─ subdir1/
    // │  ├─ file3.txt
    // │  ├─ file4.doc
    // │  └─ subsubdir/
    // │     └─ file5.txt
    // └─ subdir2/
    //    ├─ file6.txt
    //    └─ image.png
    //
    // We'll search for ".txt" files in test_dir.
    // Expected txt files: file1.txt, file2.txt, file3.txt, file5.txt, file6.txt
    // Adjust the directory path to match your setup.

    // Run by `g++ -std=c++17 -pthread main.cpp search.cpp -o main.out`

    if(argc != 4){
        std::cout << "Usage: ./main.out <run_mode> <test_directory> <extension> \n";
        return 1;
    }
    std::string runMode = std::string(argv[1]);
    std::string testDirectory = std::string(argv[2]);
    std::string extension = std::string(argv[3]);

    if(runMode == "test"){

        std::cout << "Running concurrent file search tests...\n";

        // Test 1: Basic search
        std::cout << "Test 1: Basic search for .txt files\n";
        {
            std::vector<std::string> results = searchFiles(testDirectory, extension);
            std::vector<std::string> expected = {
                "file1.txt",
                "file2.txt",
                "file3.txt",
                "file5.txt",
                "file6.txt"
            };

            // Check if all expected files are in results
            // We only check filenames, assuming no duplicates in different directories
            // For a robust test, you'd store full paths and verify them.
            bool allFound = containsAll(results, expected);

            // Additionally, verify no unexpected files
            // There should be no ".md" or ".doc" or ".png" in results
            for (auto &file : results) {
                assert(file.find(".txt") != std::string::npos && "Non-.txt file found in results!");
            }

            assert(allFound && "Not all .txt files were found!");
            std::cout << "Passed Test 1.\n";
        }

        // Test 2: No matches
        std::cout << "Test 2: Search for non-existent extension .pdf\n";
        {
            std::vector<std::string> results = searchFiles(testDirectory, ".pdf");
            for(const std::string &s : results)
                std::cout << s << std::endl;
            assert(results.empty() && "Found files when none should match!");
            std::cout << "Passed Test 2.\n";
        }

        // Test 3: Directory with no files
        // Create a directory "empty_dir" with no files to test this.
        {
            std::string emptyDir = "empty_dir"; // Make sure this directory is empty
            std::vector<std::string> results = searchFiles(emptyDir, extension);
            assert(results.empty() && "Found files in an empty directory!");
            std::cout << "Passed Test 3: Empty directory handled.\n";
        }

        // Test 4: Multiple concurrent searches
        // (Run several searches in sequence. Not fully concurrent from main’s perspective,
        // but inside `searchFiles`, multiple threads will be spawned.)
        std::cout << "Test 4: Run multiple searches in a row.\n";
        for (int i = 0; i < 3; ++i) {
            std::vector<std::string> results = searchFiles(testDirectory, extension);
            assert(!results.empty() && "Subsequent searches should still find .txt files!");
        }
        std::cout << "Passed Test 4.\n";

        // If the code reaches here without assertion failures, we consider all tests passed.
        std::cout << "All tests completed successfully.\n";
    }
    else if(runMode == "run"){
        std::cout << "Running concurrent file search...\n";
        std::vector<std::string> results = searchFiles(testDirectory, extension);
        std::cout << "Found " << results.size() << " files with extension " << extension << ":\n";
        for (const auto& file : results) {
            std::cout << file << '\n';
        }
    }
    else{
        std::cout << "Invalid run mode.\n";
    }

    return 0;
}
