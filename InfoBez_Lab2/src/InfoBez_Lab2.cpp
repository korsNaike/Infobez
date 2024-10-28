#include "InfoBez_Lab2.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include "Access.cpp"
#include "SparseMatrix.cpp"
#include "SparseMatrixJsonReader.cpp"


int main() {
    SparseMatrixJsonReader reader("X:\\Studying\\Infobez\\InfoBez_Lab2\\data.json");
    SparseMatrix matrix(1000, 1000);
    reader.read(matrix);

    // Вычисление процента заполненности
    std::cout << "Fill percentage: " << matrix.getFillPercentage() << "%" << std::endl;

    // Список субъектов с доступом к объекту
    auto accessList = matrix.listSubjectsWithAccess(1);
    std::cout << "Subjects with access to 1: ";
    for (const auto& subject : accessList) {
        std::cout << subject << " ";
    }

    int idPokemon = matrix.addSubject("Pokemon");
    matrix.addSubject("Flexich");

    matrix.editCell(idPokemon, 1, Access::WRITE, true);
    std::cout << "Fill percentage: " << matrix.getFillPercentage() << "%" << std::endl;
    for (const auto subject : matrix.subjects) {
        std::cout << subject.first << ". " << subject.second << std::endl;
    }

    reader.write(matrix);
    std::cout << "Wrote.." << std::endl;

    return 0;
}

