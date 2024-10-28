#include "InfoBez_Lab2.h"
#include "CommandExecutor.cpp"
#include "ChineseWall.cpp"

void sparseMatrix() {
    CommandExecutor executor;
    executor.run();
}

void chineseWall() {
    ChineseWallPolicy policy;

    // Пример использования
    policy.addFirm("F1");
    policy.addFirm("F2");
    policy.addFirm("F3");

    policy.addObjectToFirm("F1", "o1");
    policy.addObjectToFirm("F1", "o2");
    policy.addObjectToFirm("F2", "o3");
    policy.addObjectToFirm("F3", "o4");

    policy.addConflictClass("CI1", { "F1", "F2" });
    policy.addConflictClass("CI2", { "F2", "F3" });

    policy.addSubject("s1");
    policy.addSubject("s2");

    policy.start();

    cout << policy.read("s1", "o1") << "\n"; // accepted
    cout << policy.write("s1", "o1") << "\n"; // accepted
    cout << policy.read("s1", "o3") << "\n"; // refused
    cout << policy.write("s1", "o4") << "\n"; // refused

    policy.reportSubject("s1");
    policy.reportObject("o1");
    policy.briefCase("F1");
}

int main() {
    // chineseWall();
    sparseMatrix();
    return 0;
}

