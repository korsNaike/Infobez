#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Access.cpp"
#include "SparseMatrix.cpp"



#pragma once

struct Subject {
    std::string name;
    int id;
};

struct Record {
	int object_id;
	int subject_id;
	Access access;
};

class SparseMatrixJsonReader {
private:
    std::string filename;

    static std::pair<std::vector<Record>, std::vector<Subject>> readDataFromFile(const std::string& filename) {
        std::vector<Record> records;
        std::vector<Subject> subjects;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return std::make_pair(records, subjects);
        }

        nlohmann::json jsonData;
        file >> jsonData;

        auto accessSubjects = jsonData["subjects"];
        auto accessRecords = jsonData["accessRecords"];

        for (const auto& item : accessSubjects) {
            int id = item["id"];
            std::string name = item["name"];

            subjects.push_back({ name, id });
        }
        for (const auto& item : accessRecords) {
            int object_id = item["object_id"];
            int subject_id = item["subject_id"];
            char accessChar = item["access"].get<char>();
            Access access = (accessChar == 'r') ? Access::READ : Access::WRITE;

            records.push_back({ object_id, subject_id, access });
        }

        return std::make_pair(records, subjects);
    }

    static std::pair<int, int> getMaxObjectIdAndSubjectId(std::vector<Record> records) {
        int maxCol = 0;
        int maxRow = 0;

        for (const auto& record : records) {
            if (record.object_id > maxCol) {
                maxCol = record.object_id;
            }
            if (record.subject_id > maxRow) {
                maxRow = record.subject_id;
            }
        }

        return std::make_pair(maxCol, maxRow);
    }
public:
    SparseMatrixJsonReader() {
        this->filename = "";
    }

    SparseMatrixJsonReader(std::string filename) {
        this->filename = filename;
    }

    void read(SparseMatrix& matrix) {
        auto recordsAndSubjects = readDataFromFile(this->filename);
        auto records = recordsAndSubjects.first;
        auto subjects = recordsAndSubjects.second;

        for (auto subject : subjects) {
            matrix.addSubject(subject.name, subject.id);
        }
        for (auto record : records) {
            matrix.editCell(record.subject_id, record.object_id, record.access, true);
        }
    }

    void write(SparseMatrix& matrix) {
        nlohmann::json jsonData;

        // Запись субъектов
        for (const auto& subject : matrix.subjects) {
            jsonData["subjects"].push_back({ {"id", subject.first}, {"name", subject.second} });
        }

        // Запись записей доступа
        for (const auto& persmissions : matrix.data) {
            for (const auto& access : persmissions.second) {
                char access_char = static_cast<char>(access);
                jsonData["accessRecords"].push_back({
                    {"object_id", persmissions.first.second},
                    {"subject_id", persmissions.first.first},
                    {"access", access_char}
                    });
            }
        }

        // Запись json в 
        std::cout << "File: " << filename << std::endl;
        std::ofstream file(filename, std::ofstream::trunc); // Открытие с очисткой содержимого
        if (file.is_open()) {
            file << jsonData.dump(4); // форматируем с отступами для удобства чтения
            file.close();
        }
        else {
            std::cerr << "Could not open file for writing: " << filename << std::endl;
        }
    }
};