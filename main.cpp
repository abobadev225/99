#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

// Структура для представления книги в библиотеке
struct Book {
    string title;   // Название книги
    string author;  // Автор книги
    int year;       // Год выпуска книги
    string genre;   // Жанр книги
    int id;         // Идентификатор книги
};

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

// Функция для перевода строки в нижний регистр
void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower); // Преобразование всех символов в нижний регистр
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

// Главное меню для взаимодействия с пользователем
void menu(int& choose, Book*& library, int size) {
    while (true) {
        cout << "Choose an option from the menu:" << endl;
        cout << "1. Display all library books" << endl;
        cout << "2. Add a book to the library" << endl;
        cout << "3. Delete a book from the library" << endl;
        cout << "4. Find a specific book (by author, genre, or ID)" << endl;
        cout << "5. Exit program" << endl;
        cout << "------------------------" << endl;
        cin >> choose;  // Ввод выбора пользователя

        cin.ignore();  // Очищаем буфер ввода от лишних символов

        switch (choose) {
            case 1:
                displayBooks(library, size); // Отображение всех книг
                break;
            case 2: {
                Book newBook; // Ввод данных новой книги
                cout << "Enter book title: ";
                getline(cin, newBook.title);
                cout << "Enter author: ";
                getline(cin, newBook.author);
                cout << "Enter year: ";
                cin >> newBook.year;
                cin.ignore();
                cout << "Enter genre: ";
                getline(cin, newBook.genre);
                newBook.id = size + 1; // Генерация ID книги
                addBook(library, size, newBook); // Добавление книги
                break;
            }
            case 3: {
                int deleteId; // Удаление книги по ID
                cout << "Enter the ID of the book to delete: ";
                cin >> deleteId;
                cin.ignore();
                bool found = false;
                for (int i = 0; i < size; i++) {
                    if (library[i].id == deleteId) {
                        found = true;
                        for (int j = i; j < size - 1; j++) {
                            library[j] = library[j + 1]; // Перемещение книг
                        }
                        size--; // Уменьшение размера библиотеки
                        cout << "Book with ID " << deleteId << " deleted successfully!" << endl;
                        break;
                    }
                }
                if (!found) {
                    cout << "No book found with this ID." << endl; // Если книга не найдена
                }
                break;
            }
            case 4: {
                string search;
                cout << "Enter author, genre, or ID to search for a book: ";
                getline(cin, search); // Ввод поискового запроса
                findBook(library, size, search); // Поиск книги
                break;
            }
            case 5:
                cout << "Exiting program..." << endl; // Выход из программы
                return;
            default:
                cout << "Invalid option. Try again." << endl; // Некорректный ввод
                break;
        }
    }
}

int main() {
    Book* library = nullptr; // Указатель на библиотеку

    int size = 0; // Размер библиотеки

    loadBooksFromFile("lib.txt", library, size); // Загрузка книг из файла
    int choose;

    menu(choose, library, size); // Вызов меню

    this_thread::sleep_for(seconds(1)); // Ожидание перед завершением программы

    delete[] library; // Освобождение памяти

    return 0;
}
