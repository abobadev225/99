#include "file_utils.h"
#include <iostream>
#include <fstream>

// Функция для загрузки книг из файла
void loadBooksFromFile(const string& filename, Book*& library, int& size) {
    ifstream file(filename);  // Открытие файла для чтения

    if (!file) {
        cerr << "file reading error." << endl; // Если файл не открылся
        return;
    }

    while (true) {
        Book newBook;
        string yearStr, idStr;

        if (!getline(file, newBook.title)) break; // Чтение названия книги
        if (!getline(file, newBook.author)) break; // Чтение автора книги
        if (!getline(file, yearStr)) break; // Чтение года выпуска
        if (!getline(file, newBook.genre)) break; // Чтение жанра книги
        if (!getline(file, idStr)) break; // Чтение ID книги

        newBook.year = stoi(yearStr);  // Преобразование строки года в число
        newBook.id = stoi(idStr);      // Преобразование строки ID в число

        addBook(library, size, newBook); // Добавление книги в библиотеку

        string emptyLine;
        getline(file, emptyLine); // Пропуск пустой строки
    }

    file.close();  // Закрытие файла
    cout << "Books from file are loaded." << endl;
}