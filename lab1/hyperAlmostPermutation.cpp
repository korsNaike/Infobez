#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include "hyperAlmostPermutatuion.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>

// Функция проверки, является ли строка почти перестановочной
bool isAlmostPermutative(const std::string& s, int N) {
    std::unordered_set<char> characters;
    for (char c : s) {
        characters.insert(c);
    }
    return characters.size() == N;
}

// Основная функция для поиска гипер почти перестановочной строки
std::string findHyperAlmostPermutativeString(const std::string& S1, const std::string& S2, int N) {
    std::string candidate = S1 + S2;
    return candidate;
}

int main_hyper() {
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");

    int N;
    std::string S1, S2;

    if (infile.is_open()) {
        infile >> N >> S1 >> S2;
        infile.close();
    }

    std::string result = findHyperAlmostPermutativeString(S1, S2, N);

    if (outfile.is_open()) {
        outfile << result << std::endl;
        outfile.close();
    }

    return 0;
}
