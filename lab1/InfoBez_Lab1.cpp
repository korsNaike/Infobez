#include <iostream>
#include <stack>
#include <string>
#include "hyperAlmostPermutatuion.h"

std::string restore_text(const std::string& encrypted) {
    std::stack<char> char_stack;

    for (char c : encrypted) {
        // Если стек не пуст и верхний элемент совпадает с текущим символом
        if (!char_stack.empty() && char_stack.top() == c) {
            char_stack.pop(); // Удаляем верхний элемент (формируется пара)
        }
        else {
            char_stack.push(c); // Добавляем текущий символ в стек
        }
    }

    std::string restored_text;

    // Извлекаем символы из стека, чтобы получить восстановленный текст
    while (!char_stack.empty()) {
        restored_text = char_stack.top() + restored_text; // Формируем строку в обратном порядке
        char_stack.pop();
    }

    return restored_text;
}

int main_restore() {
    std::string encrypted;
    std::cout << "Input encrypted text: " << std::endl;
    std::cin >> encrypted; // Считываем зашифрованный текст

    std::string restored_text = restore_text(encrypted);

    std::cout << "Result: " << restored_text << std::endl; // Вывод восстановленного текста

    return 0;
}

int main() {
    // main_restore();
    main_hyper();

    return 0;
}
