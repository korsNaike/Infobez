#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "SparseMatrix.cpp"
#include "SparseMatrixJsonReader.cpp"

class CommandExecutor {
public:
    CommandExecutor() : selectedIndex(0) {}

    void run() {
        requestFileName();
        displayMenu();
    }

private:
    std::string fileName;
    int selectedIndex;
    std::vector<std::string> menuOptions = {
        "Edit cell in Access Matrix",
        "Add new subject",
        "Delete subject",
        "Print fill percentage",
        "Print list of subjects with access to object",
        "Save",
        "Exit"
    };
    SparseMatrixJsonReader reader;
    SparseMatrix matrix = SparseMatrix(1000, 1000);

    void requestFileName() {
        std::cout << "Enter the file name: ";
        std::getline(std::cin, fileName);
        reader = SparseMatrixJsonReader(fileName);
        reader.read(matrix);
    }

    void displayMenu() {
        bool running = true;
        while (running) {
            system("cls"); // Очищает экран (для Windows). Для Linux/Unix можно использовать "clear".
            std::cout << "Selected file: " << fileName << "\n";
            std::cout << "Use arrow keys to navigate, press Enter to select an option.\n\n";
            displayOptions();

            int key = _getch(); // Получает нажатую клавишу
            switch (key) {
            case 72: // Вверх
                selectedIndex = (selectedIndex - 1 + menuOptions.size()) % menuOptions.size();
                break;
            case 80: // Вниз
                selectedIndex = (selectedIndex + 1) % menuOptions.size();
                break;
            case 13: // Enter
                running = executeOption();
                break;
            }
        }
    }

    void displayOptions() const {
        for (int i = 0; i < menuOptions.size(); ++i) {
            if (i == selectedIndex) {
                std::cout << "> " << menuOptions[i] << "\n";
            }
            else {
                std::cout << "  " << menuOptions[i] << "\n";
            }
        }
    }

    bool executeOption() {
        switch (selectedIndex) {
        case 0:
            editCell();
            break;
        case 1:
            addNewSubject();
            break;
        case 2:
            deleteSubject();
            break;
        case 3:
            printFillPercentage();
            break;
        case 4:
            printListSubjects();
            break;
        case 5:
            save();
            break;
        case 6:
            return false; // Завершить работу
        }
        return true;
    }

    void editCell() {
        int subject_id, object_id, add_or_edit;
        std::string access;
        std::cout << "\nEnter subject number: ";
        std::cin >> subject_id;
        
        std::cout << "\nEnter object number: ";
        std::cin >> object_id;

        std::cout << "\nYou wanna add or delete the access? (0 to delete, 1 to add): ";
        std::cin >> add_or_edit;

        if (add_or_edit == 0) {
            matrix.editCell(subject_id, object_id, Access::READ, false);
            std::cout << "\nAccess successfully removed!\n";
            system("pause");
            return;
        }

        std::cout << "\nWhat access do you want to add? ('r' to read, 'w' to write): ";
        std::cin >> access;

        if (access != "r" && access != "w") {
            std::cout << "\nInvalid value!";
            system("pause");
            return;
        }
        Access acc = access == "r" ? Access::READ : Access::WRITE;

        matrix.editCell(subject_id, object_id, acc, true);
        std::cout << "\nAccess successfully added!\n";
        system("pause");
    }

    void addNewSubject() {
       std::string subject_name;
       std::cout << "\nEnter subject number: ";
       std::cin >> subject_name;

       int newId = matrix.addSubject(subject_name);
       std::cout << "\n" << subject_name << " was added successfully! ID: " << newId << std::endl;
       system("pause");
    }

    void deleteSubject() {
        int subject_id;
        std::cout << "\nEnter subject ID: ";
        std::cin >> subject_id;

        matrix.deleteSubject(subject_id);
        std::cout << "\nSubject was removed successfully!" << std::endl;
        system("pause");
    }

    void printFillPercentage() {
        std::cout << "\nFill percentage: " << matrix.getFillPercentage() << "%" << std::endl;
        system("pause");
    }

    void printListSubjects() {
        int object_id;
        std::cout << "\nEnter object ID: ";
        std::cin >> object_id;

        // Список субъектов с доступом к объекту
        auto accessList = matrix.listSubjectsWithAccess(object_id);
        std::cout << "\nSubjects with access to " << object_id << ":";
        for (const auto& subject : accessList) {
            std::cout << subject << " ";
        }
        system("pause");
    }

    void save() {
        reader.write(matrix);
        std::cout << "\nChanges saved!\n";
        system("pause");
    }
};