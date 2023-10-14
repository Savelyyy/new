#include <string>
#include <vector>
#include <sstream>


// Функция для сравнения версий в числовом формате
bool compareVersionsAndRelease(const std::string& version1, const std::string& version2,
                               const std::string& release1, const std::string& release2) {
    // Сначала сравниваем версии
    std::vector<int> components1;
    std::vector<int> components2;

    std::istringstream ss1(version1);
    std::istringstream ss2(version2);

    int component;
    char delimiter;

    while (ss1 >> component) {
        components1.push_back(component);
        ss1 >> delimiter;
    }

    while (ss2 >> component) {
        components2.push_back(component);
        ss2 >> delimiter;
    }

    for (size_t i = 0; i < std::min(components1.size(), components2.size()); ++i) {
        if (components1[i] < components2[i]) {
            return false;
        } else if (components1[i] > components2[i]) {
            return true;
        }
    }

    if (components1.size() > components2.size()) {
        return true;
    } else if (components1.size() < components2.size()) {
        return false;
    }

    // Если версии совпадают, сравниваем release
    return release1 < release2;
}
