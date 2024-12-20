#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <filesystem>
#include <algorithm>
#include <functional>
#include <atomic>

#include "search.h"

std::vector<std::string> foundFiles;
std::vector<std::thread> threadList;
std::queue<std::filesystem::path> directoryQueue;

std::mutex mtxFiles;
std::mutex mtxDirs;
std::condition_variable cv_queue;

std::atomic<int> activeWork{0};

void cleanUp() {
    std::queue<std::filesystem::path> empty;
    std::swap(directoryQueue, empty);

    for (auto &t : threadList) {
        if (t.joinable()) t.join();
    }

    threadList.clear();
    activeWork = 0;
}

std::vector<std::string> searchFiles(std::string directory, std::string fileExtension) {
    {
        std::lock_guard<std::mutex> lock1(mtxFiles);
        std::lock_guard<std::mutex> lock2(mtxDirs);

        foundFiles.clear();
    }

    directoryQueue.push(std::filesystem::path(directory));

    while (true) {
        std::unique_lock<std::mutex> lockDir(mtxDirs);
        cv_queue.wait(lockDir, [&] { return !directoryQueue.empty() || activeWork == 0; });

        if (!directoryQueue.empty()) {

            std::filesystem::path next = directoryQueue.front();
            directoryQueue.pop();
            threadList.emplace_back(processDirectory, next.string(), fileExtension);
            activeWork++;

        } else if (activeWork == 0) break;
    }

    cleanUp();

    return foundFiles;
}

void processDirectory(std::string directory, std::string fileExtension) {

    if (std::filesystem::exists(directory)) {

        for (const auto& entry : std::filesystem::directory_iterator(directory)) {

            if (entry.is_directory()) {
                {
                    std::lock_guard<std::mutex> lockDirs(mtxDirs);
                    directoryQueue.push(entry.path());
                }
                cv_queue.notify_one();

            } else if (entry.path().extension() == fileExtension) {
                std::lock_guard<std::mutex> lockFiles(mtxFiles);
                foundFiles.push_back(entry.path().filename().string());
            }
        }
    }

    activeWork--;
    cv_queue.notify_one();

}
