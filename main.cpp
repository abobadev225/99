#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;
struct Book {
    string title;
    string author;
    int year;
    string genre;
    int id;
};




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

void loadBooksFromFile(const string& filename, Book*& library, int& size) {
    ifstream file(filename);

    if (!file) {
        cerr << "file reading error." << endl;
        return;
    }

    while (true) {
        Book newBook;
        string yearStr, idStr;

        if (!getline(file, newBook.title)) break;
        if (!getline(file, newBook.author)) break;
        if (!getline(file, yearStr)) break;
        if (!getline(file, newBook.genre)) break;
        if (!getline(file, idStr)) break;


        newBook.year = stoi(yearStr);
        newBook.id = stoi(idStr);


        addBook(library, size, newBook);


        string emptyLine;
        getline(file, emptyLine);
    }

    file.close();
    cout << "Books from file are loaded." << endl;
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
void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}
void findBook(Book* library, int size, const string& find) {
    int found = 0;
    string findLower = find;
    toLowerCase(findLower);
    int findId = -1;


    try {
        findId = stoi(findLower);
    } catch (...) {
        findId = -1;
    }

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
            found++;
        }
        else if (titleLower == findLower) {
            cout << "Found a book with this title!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found++;
        }
        else if (genreLower == findLower) {
            cout << "Found a book of this genre!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found++;
        }
        else if (library[i].id == findId) {
            cout << "Found a book with this ID!" << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Year: " << library[i].year << endl;
            cout << "Genre: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found++;
        }
    }

    if (found == 0) {
        cout << "Book not found." << endl;
    }
}
void menu(int& choose, Book*& library, int size) {
    while (true) {
        cout << "Choose an option from the menu:" << endl;
        cout << "1. Display all library books" << endl;
        cout << "2. Add a book to the library" << endl;
        cout << "3. Delete a book from the library" << endl;
        cout << "4. Find a specific book (by author, genre, or ID)" << endl;
        cout << "5. Exit program" << endl;
        cout << "------------------------" << endl;
        cin >> choose;


        cin.ignore();

        switch (choose) {
            case 1:
                displayBooks(library, size);
                break;
            case 2: {
                Book newBook;
                cout << "Enter book title: ";
                getline(cin, newBook.title);
                cout << "Enter author: ";
                getline(cin, newBook.author);
                cout << "Enter year: ";
                cin >> newBook.year;
                cin.ignore();
                cout << "Enter genre: ";
                getline(cin, newBook.genre);
                newBook.id = size + 1;
                addBook(library, size, newBook);
                break;
            }
            case 3: {
                int deleteId;
                cout << "Enter the ID of the book to delete: ";
                cin >> deleteId;
                cin.ignore();
                bool found = false;
                for (int i = 0; i < size; i++) {
                    if (library[i].id == deleteId) {
                        found = true;
                        for (int j = i; j < size - 1; j++) {
                            library[j] = library[j + 1];
                        }
                        size--;
                        cout << "Book with ID " << deleteId << " deleted successfully!" << endl;
                        break;
                    }
                }
                if (!found) {
                    cout << "No book found with this ID." << endl;
                }
                break;
            }
            case 4: {
                string search;
                cout << "Enter author, genre, or ID to search for a book: ";
                getline(cin, search);
                findBook(library, size, search);
                break;
            }
            case 5:
                cout << "Exiting program..." << endl;
                return;
            default:
                cout << "Invalid option. Try again." << endl;
                break;
        }
    }
}

int main() {
    Book* library = nullptr;

    int size = 0;

    loadBooksFromFile("lib.txt", library, size);
    int choose;

    menu(choose,library,size);

    this_thread::sleep_for(seconds(1));

    delete[] library;

    return 0;
}