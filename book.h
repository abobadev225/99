#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int year;
    string genre;
    int id;
};

void addBook(Book*& library, int& size, const Book& newBook);
void displayBooks(const Book* library, int size);
void findBook(Book* library, int size, const string& find);
void toLowerCase(string& str);

#endif // BOOK_H
