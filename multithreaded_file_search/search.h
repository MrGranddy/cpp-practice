#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

std::vector<std::string> searchFiles(std::string directory, std::string fileExtension);
void processDirectory(std::string directory, std::string fileExtension);

#endif