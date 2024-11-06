#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

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


void removeBook(Book*& library, int& size, int bookId) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (library[i].id == bookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Книгу з ідентифікатором " << bookId << " не знайдено." << endl;
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
        cout << "Ідентифікатор: " << library[i].id << endl;
        cout << "Назва: " << library[i].title << endl;
        cout << "Автор: " << library[i].author << endl;
        cout << "Рік видання: " << library[i].year << endl;
        cout << "Жанр: " << library[i].genre << endl;
        cout << "------------------------" << endl;
    }
}
void findBook(Book* library, int size, const string& find) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (find == library[i].author) {
            cout << "Знайдена книга від цього автора!" << endl;
            cout << "Назва: " << library[i].title << endl;
            cout << "Автор: " << library[i].author << endl;
            cout << "Рік видання: " << library[i].year << endl;
            cout << "Жанр: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
        else if (find == library[i].title) {
            cout << "Знайдена книга з цією назвою!" << endl;
            cout << "Назва: " << library[i].title << endl;
            cout << "Автор: " << library[i].author << endl;
            cout << "Рік видання: " << library[i].year << endl;
            cout << "Жанр: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
        else if (find == library[i].genre) {
            cout << "Знайдена книга цього жанру!" << endl;
            cout << "Назва: " << library[i].title << endl;
            cout << "Автор: " << library[i].author << endl;
            cout << "Рік видання: " << library[i].year << endl;
            cout << "Жанр: " << library[i].genre << endl;
            cout << "------------------------" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Книга не знайдена." << endl;
    }
}
int main() {
    system("chcp 65001 > nul");
    Book* library = nullptr;
    int size = 0;
    string find;
    Book book1 = { "Війна і мир", "Лев Толстой", 1869, "Роман", 1 };
    addBook(library, size, book1);

    Book book2 = { "1984", "Джордж Орвелл", 1949, "Антиутопія", 2 };
    addBook(library, size, book2);


    cout << "Колекція книг:" << endl;
    displayBooks(library, size);

    removeBook(library, size, 1);

    cout << "find a book" << endl;
    cin >> find;
    findBook(library, size, find);
    delete[] library;

    return 0;
}

