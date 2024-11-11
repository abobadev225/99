#include "book.h"
#include <iostream>
#include <algorithm>

// Функция для добавления книги в библиотеку
void addBook(Book*& library, int& size, const Book& newBook) {
    Book* newLibrary = new Book[size + 1]; // Создание нового массива для книг
    for (int i = 0; i < size; i++) {
        newLibrary[i] = library[i]; // Копирование старых книг в новый массив
    }
    newLibrary[size] = newBook; // Добавление новой книги
    delete[] library;           // Удаление старого массива
    library = newLibrary;       // Обновление указателя на новый массив
    size++;                      // Увеличение размера библиотеки
}


// Функция для отображения всех книг в библиотеке
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
// Функция для поиска книги по автору, жанру или ID
void findBook(Book* library, int size, const string& find) {
    int found = 0;  // Счетчик найденных книг
    string findLower = find;
    toLowerCase(findLower);  // Преобразование строки поиска в нижний регистр
    int findId = -1;

    // Попытка преобразовать строку поиска в число (ID)
    try {
        findId = stoi(findLower);
    } catch (...) {
        findId = -1; // Если не удалось преобразовать, считаем что это не ID
    }

    for (int i = 0; i < size; i++) {
        string titleLower = library[i].title;
        string authorLower = library[i].author;
        string genreLower = library[i].genre;

        toLowerCase(titleLower);  // Преобразование данных книги в нижний регистр
        toLowerCase(authorLower);
        toLowerCase(genreLower);

        // Сравнение данных книги с поисковой строкой
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
        cout << "Book not found." << endl; // Если книга не найдена
    }
}

// Функция для перевода строки в нижний регистр
void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower); // Преобразование всех символов в нижний регистр
}



