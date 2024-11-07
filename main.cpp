#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
struct Book {
    string title;
    string author;
    int year;
    string genre;
    int id;
};

void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void addBook(Book*& library, int& size, const Book& newBook) {
    Book* newLibrary = new Book[size + 1];
    for (int i = 0; i < size; i++) {
        newLibrary[i] = library[i];
    }
    newLibrary[size] = newBook;
    delete[] library;
    library = newLibrary;
    size++;
}

void removeBook(Book*& library, int& size, int bookId) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (library[i].id == bookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book with ID " << bookId << " not found." << endl;
        return;
    }

    Book* newLibrary = new Book[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            newLibrary[j] = library[i];
            j++;
        }
    }
    delete[] library;
    library = newLibrary;
    size--;
}

void displayBooks(const Book* library, int size) {
    for (int i = 0; i < size; i++) {
        cout << "ID: " << library[i].id << endl;
        cout << "Title: " << library[i].title << endl;
        cout << "Author: " << library[i].author << endl;
        cout << "Year: " << library[i].year << endl;
        cout << "Genre: " << library[i].genre << endl;
        cout << "------------------------" << endl;
    }
}

void findBook(Book* library, int size, const string& find) {
    bool found = false;
    string findLower = find;
    toLowerCase(findLower);

    for (int i = 0; i < size; i++) {
        string titleLower = library[i].title;
        string authorLower = library[i].author;
        string genreLower = library[i].genre;

        toLowerCase(titleLower);
        toLowerCase(authorLower);
        toLowerCase(genreLower);

        if (authorLower == findLower) {
            cout << "Found a book by this author!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
        else if (titleLower == findLower) {
            cout << "Found a book with this title!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
        else if (genreLower == findLower) {
            cout << "Found a book of this genre!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found." << endl;
    }
}

int main() {
    system("chcp 65001 > nul");

    Book* library = nullptr;
    int size = 0;
    string find;

    Book book1 = { "War and Peace", "Leo Tolstoy", 1869, "Novel", 1 };
    addBook(library, size, book1);
    Book book2 = { "1984", "George Orwell", 1949, "Dystopia", 2 };
    addBook(library, size, book2);

    cout << "Book Collection:" << endl;
    displayBooks(library, size);

    cout << "Search for a book by title, author, or genre:" << endl;

    getline(cin, find);

    cout << "Entered search string: " << find << endl;

    findBook(library, size, find);
    sleep_for(seconds(4));
    delete[] library;
    return 0;
}
