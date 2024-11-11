#include <iostream>
#include <chrono>
#include <thread>
#include "book.h"
#include "file_utils.h"

using namespace std;
using namespace std::chrono;

// Главное меню для взаимодействия с пользователем
void menu(int& choose, Book*& library, int size) {
    while (true) {
        cout << "------------------------" << endl;
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
                        size--; // Уменьшение размера библиотекисвою прогу накалякал
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
    Book* library = nullptr;
    int size = 0;

    loadBooksFromFile("lib.txt", library, size);
    int choose;
    menu(choose, library, size);
    this_thread::sleep_for(seconds(1));
    delete[] library;
    return 0;
}
