#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include "book.h"
using namespace std;

void loadBooksFromFile(const string& filename, Book*& library, int& size);

#endif // FILE_UTILS_H
