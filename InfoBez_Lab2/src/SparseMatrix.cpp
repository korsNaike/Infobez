#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include "Access.cpp"

#pragma once

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            size_t hash1 = hash<int>()(p.first);
            size_t hash2 = hash<int>()(p.second);
            return hash1 ^ (hash2 << 1); // Сдвиг второго хеша
        }
    };
}

class SparseMatrix {
private:
    int n, m;

    int currentId;

public:
    std::unordered_map<std::pair<int, int>, std::unordered_set<Access>, std::hash<std::pair<int, int>>> data;

    std::unordered_map<int, std::string> subjects; // Субъекты

    SparseMatrix(int n, int m) : n(n), m(m), currentId(1) {}

    int addSubject(const std::string& name) {
        subjects[currentId] = name;
        return currentId++;
    }

    int addSubject(const std::string& name, int id) {
        subjects[id] = name;
        currentId = id + 1;
        return id;
    }

    void deleteSubject(int subjectId) {
        if (subjects.erase(subjectId)) {
            for (auto& entry : data) {
                entry.second.clear();
            }
        }
        else {
            std::cout << "Субъект не найден." << std::endl;
        }
    }

    void editCell(int subject_id, int object_id, Access permission, bool add) {
        auto key = std::make_pair(subject_id, object_id);
        if (add) {
            data[key].insert(permission);
        }
        else {
            data[key].erase(permission);
        }
    }

    double getFillPercentage() const {
        double totalCells = n * m;
        double nonDefaultCells = data.size();
        return (nonDefaultCells / totalCells) * 100;
    }

    std::vector<int> listSubjectsWithAccess(int obj) {
        std::vector<int> result;
        for (auto subjectId : subjects) {
            auto key = std::make_pair(subjectId.first, obj);
            if (data.find(key) != data.end()) {
                result.push_back(subjectId.first);
            }
        }

        return result;
    }
};