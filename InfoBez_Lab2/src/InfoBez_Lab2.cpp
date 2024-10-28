#include "InfoBez_Lab2.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include "Access.cpp"
#include "SparseMatrix.cpp"
#include "SparseMatrixJsonReader.cpp"

void flex() {
    SparseMatrix matrix(1000, 1000); // Пример количества субъектов и объектов

// Добавление субъектов
    int id1 = matrix.addSubject("Bell");
    int id2 = matrix.addSubject("Alice");
    std::cout << "Bell has been registered as " << id1 << std::endl;
    std::cout << "Alice has been registered as " << id2 << std::endl;

    // Редактирование клеток
    matrix.editCell(id1, 1, Access::READ, true); // Bell имеет доступ к чтению объекта 1
    matrix.editCell(id2, 1, Access::READ, true); // Alice также имеет доступ к объекту 1
    matrix.editCell(id1, 2, Access::WRITE, true); // Bell имеет доступ write объекта 2

    // Вычисление процента заполненности
    std::cout << "Fill percentage: " << matrix.getFillPercentage() << "%" << std::endl;

    // Список субъектов с доступом к объекту
    auto accessList = matrix.listSubjectsWithAccess(1);
    std::cout << "Subjects with access to 1: ";
    for (const auto& subject : accessList) {
        std::cout << subject << " ";
    }
    std::cout << std::endl;

    // Удаление субъекта
    matrix.deleteSubject(id1);
    std::cout << "Subjects after deleting Bell: ";
    for (const auto& pair : matrix.subjects) {
        std::cout << pair.second << " ";
    }
    std::cout << std::endl;
}

int main() {
    SparseMatrixJsonReader reader("C:\\Users\\79186\\source\\repos\\InfoBez_Lab2\\data.json");
    auto matrix = reader.read();

    // Вычисление процента заполненности
    std::cout << "Fill percentage: " << matrix.getFillPercentage() << "%" << std::endl;

    // Список субъектов с доступом к объекту
    auto accessList = matrix.listSubjectsWithAccess(1);
    std::cout << "Subjects with access to 1: ";
    for (const auto& subject : accessList) {
        std::cout << subject << " ";
    }
    std::cout << std::endl;

    return 0;
}

