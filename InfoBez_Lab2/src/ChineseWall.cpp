#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <optional>
using namespace std;

//  ласс, представл€ющий фирму
class Firm {
public:
    string name;
    vector<string> portfolio; // объекты в портфеле фирмы

    Firm() {
        name = "empty";
    }

    Firm(string name) : name(name) {}

    void addObject(const string& object) {
        portfolio.push_back(object);
    }
};

//  ласс, представл€ющий субъект
class FirmSubject {
public:
    string name;
    unordered_map<string, string> accessedObjects; // объект -> фирма
    unordered_set<string> conflictClasses; // классы конфликтов, к которым обращалс€ субъект

    FirmSubject() {
        name = "Empty";
    }

    FirmSubject(string name) : name(name) {}
};

//  ласс, представл€ющий политику доступа " итайска€ стена"
class ChineseWallPolicy {
public:
    unordered_map<string, Firm> firms; // фирма -> объект фирмы
    unordered_map<string, unordered_set<string>> conflictClasses; // класс конфликта -> фирмы
    unordered_map<string, FirmSubject> subjects; // субъект -> объект субъекта

    void addFirm(const string& firmName) {
        firms[firmName] = Firm(firmName);
    }

    void addObjectToFirm(const string& firmName, const string& objectName) {
        firms[firmName].addObject(objectName);
    }

    void addConflictClass(const string& conflictClassName, const vector<string>& firmNames) {
        for (const string& firmName : firmNames) {
            conflictClasses[conflictClassName].insert(firmName);
        }
    }

    void addSubject(const string& subjectName) {
        subjects[subjectName] = FirmSubject(subjectName);
    }

    void start() {
        for (auto& [subjectName, subject] : subjects) {
            subject.accessedObjects.clear();
            subject.conflictClasses.clear();
        }
    }

    string read(const string& subjectName, const string& objectName) {
        if (!subjects.count(subjectName)) return "FirmSubject not found";
        if (!getFirmOfObject(objectName)) return "Object not found";

        string firmName = *getFirmOfObject(objectName);
        string conflictClass = getConflictClass(firmName);

        FirmSubject& subject = subjects[subjectName];
        if (subject.accessedObjects.count(objectName) ||
            !conflictClass.empty() && subject.conflictClasses.count(conflictClass) &&
            subject.accessedObjects[objectName] != firmName) {
            return "refused";
        }

        subject.accessedObjects[objectName] = firmName;
        if (!conflictClass.empty()) {
            subject.conflictClasses.insert(conflictClass);
        }
        return "accepted";
    }

    string write(const string& subjectName, const string& objectName) {
        if (read(subjectName, objectName) == "refused") return "refused";

        string firmName = *getFirmOfObject(objectName);
        string conflictClass = getConflictClass(firmName);

        FirmSubject& subject = subjects[subjectName];
        for (const auto& [accessedObject, accessedFirm] : subject.accessedObjects) {
            if (accessedFirm != firmName && conflictClass == getConflictClass(accessedFirm)) {
                return "refused";
            }
        }
        return "accepted";
    }

    void reportSubject(const string& subjectName) const {
        if (!subjects.count(subjectName)) {
            cout << "FirmSubject not found\n";
            return;
        }
        const FirmSubject& subject = subjects.at(subjectName);
        cout << "Report for " << subjectName << ":\n";
        for (const auto& [object, firm] : subject.accessedObjects) {
            cout << "  Object: " << object << ", Firm: " << firm << "\n";
        }
    }

    void reportObject(const string& objectName) const {
        cout << "Report for " << objectName << ":\n";
        for (const auto& [subjectName, subject] : subjects) {
            if (subject.accessedObjects.count(objectName)) {
                cout << "  Accessed by: " << subjectName << "\n";
            }
        }
    }

    void briefCase(const string& firmName) const {
        if (!firms.count(firmName)) {
            cout << "Firm not found\n";
            return;
        }
        const Firm& firm = firms.at(firmName);
        cout << "Briefcase for " << firmName << ":\n";
        for (const string& object : firm.portfolio) {
            cout << "  Object: " << object << "\n";
        }
    }

private:
    optional<string> getFirmOfObject(const string& objectName) const {
        for (const auto& [firmName, firm] : firms) {
            if (find(firm.portfolio.begin(), firm.portfolio.end(), objectName) != firm.portfolio.end()) {
                return firmName;
            }
        }
        return nullopt;
    }

    string getConflictClass(const string& firmName) const {
        for (const auto& [conflictClassName, firmSet] : conflictClasses) {
            if (firmSet.count(firmName)) {
                return conflictClassName;
            }
        }
        return "";
    }
};